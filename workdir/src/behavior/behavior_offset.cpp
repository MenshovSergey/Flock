#include <behavior/behavior_offset.h>

namespace behavior
{
    void behavior_offset::apply(object::dynamic_object * obj)
    {
        state temp = obj->get_state();
        state t_state = target_->get_state();
        point_3d to_object(t_state.coord.x - temp.coord.x, t_state.coord.y - temp.coord.y, t_state.coord.z - temp.coord.z);
        point_3d expect = interpolation(target_, obj);
        point_3d to_target(expect.x - temp.coord.x, expect.y - temp.coord.y, expect.z - temp.coord.z);
        to_target /= abs(to_target);
        point_3d cur_speed = temp.speed /= abs (temp.speed);
        if (abs(to_object) > 2 * offset_)
        {
            point_3d new_force = to_target - cur_speed;
            obj->full_force(new_force);
        }
        else
        {
            point_3d new_force = (to_target - cur_speed) * (abs(to_object) - offset_) / offset_ + ((t_state.speed / abs(t_state.speed)) - cur_speed) * ( offset_ - fabs(abs(to_object) - offset_)) / offset_;
            obj->full_force(new_force);
        }
    }

    void behavior_offset::init(double new_offset)
    {
        offset_ = new_offset;
    }

    behavior_offset::behavior_offset(object::object_mod * target)
        : target_(target)
    {
    }

    behavior_offset::behavior_offset(object::object_mod * target, double offset)
        : target_(target)
        , offset_(offset)
    {
    }

    behavior_offset::~behavior_offset()
    {
    }
} //behavior
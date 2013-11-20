#include <behavior/behavior_pursuit.h>

namespace behavior
{
    void behavior_pursuit::apply(object::dynamic_object * obj)
    {
        state temp = obj->get_state();
        point_3d expect = interpolation(target_, obj);
        point_3d to_target(expect.x - temp.coord.x, expect.y - temp.coord.y, expect.z - temp.coord.z);
        to_target /= abs(to_target);
        point_3d cur_speed = temp.speed /= abs (temp.speed);
        point_3d new_force = to_target - cur_speed;
        obj->full_force(new_force);
    }

    behavior_pursuit::behavior_pursuit(object::object_mod * target)
    {
        target_ = target;
    }

    behavior_pursuit::~behavior_pursuit()
    {
    }

    void behavior_evade::apply(object::dynamic_object * obj)
    {
        state temp = obj->get_state();
        point_3d expect = interpolation(target_, obj);
        point_3d to_target(expect.x - temp.coord.x, expect.y - temp.coord.y, expect.z - temp.coord.z);
        to_target /= abs(to_target);
        point_3d cur_speed = temp.speed /= abs (temp.speed);
        point_3d new_force = - to_target - cur_speed;
        obj->full_force(new_force);
    }

    behavior_evade::behavior_evade(object::object_mod * target)
    {
        target_ = target;
    }

    behavior_evade::~behavior_evade()
    {
    }

    

    point_3d interpolation(object::object_mod * target, object::dynamic_object * obj)
    {
        state target_state = target->get_state(); //UNDONE
        return target_state.coord;
    }

} //behavior
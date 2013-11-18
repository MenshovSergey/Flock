#include <behavior/behavior_seek.h>

namespace behavior
{

    void behavior_seek::apply (object::dynamic_object * obj)
    {
        state temp = obj->get_state();
        point_3d to_target(target_.x - temp.coord.x, target_.y - temp.coord.y, target_.z - temp.coord.z);
        to_target /= abs(to_target);
        point_3d cur_speed = temp.speed /= abs (temp.speed);
        point_3d new_force = to_target - cur_speed;
        obj->full_force(new_force);
    }

    void behavior_seek::init (point_3d new_target)
    {
        target_ = new_target;
    }

    behavior_seek::behavior_seek(point_3d target)
        : target_(target)
    {
    }

    behavior_seek::~behavior_seek()
    {
    }

    void behavior_flee::apply (object::dynamic_object * obj)
    {
        state temp = obj->get_state();
        point_3d to_target(target_.x - temp.coord.x, target_.y - temp.coord.y, target_.z - temp.coord.z);
        to_target /= abs(to_target);
        point_3d cur_speed = temp.speed /= abs (temp.speed);
        point_3d new_force = - to_target - cur_speed;
        obj->full_force(new_force);
    }

    void behavior_flee::init (point_3d new_target)
    {
        target_ = new_target;
    }

    behavior_flee::behavior_flee(point_3d target)
        : target_(target)
    {
    }

    behavior_flee::~behavior_flee()
    {
    }

} //behavior
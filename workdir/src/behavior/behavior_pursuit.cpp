#include <behavior/behavior_pursuit.h>
#include "typedef/typedef.h"
namespace behavior
{
    void behavior_pursuit::apply(boost::shared_ptr<object::dynamic_object>  obj)
    {
        state temp = obj->get_state();
        point_3d expect = interpolation(target_, obj);
        point_3d to_target(expect.x - temp.coord.x, expect.y - temp.coord.y, expect.z - temp.coord.z);
        to_target /= abs(to_target);
		point_3d cur_speed;
		if (abs(temp.speed) != 0)
		{
            cur_speed = temp.speed /= abs (temp.speed);
		}
        point_3d new_force = to_target - cur_speed;
        obj->full_force(new_force);
    }

    behavior_pursuit::behavior_pursuit(boost::shared_ptr<object::object_mod>  target)
    {
        target_ = target;
    }

    behavior_pursuit::~behavior_pursuit()
    {
    }

    void behavior_evade::apply(boost::shared_ptr<object::dynamic_object> obj)
    {
        state temp = obj->get_state();
        point_3d expect = interpolation(target_, obj);
        point_3d to_target(expect.x - temp.coord.x, expect.y - temp.coord.y, expect.z - temp.coord.z);
        to_target /= abs(to_target);
		point_3d cur_speed;
        if (abs(temp.speed) != 0)
		{
            cur_speed = temp.speed /= abs (temp.speed);
		}
        point_3d new_force = - to_target - cur_speed;
        obj->full_force(new_force);
    }

    behavior_evade::behavior_evade(boost::shared_ptr<object::object_mod> target)
    {
        target_ = target;
    }

    behavior_evade::~behavior_evade()
    {
    }

    void behavior_evade_rad::apply(boost::shared_ptr<object::dynamic_object> obj)
    {
        state temp = obj->get_state();
        point_3d expect = interpolation(target_, obj);
        point_3d to_target(expect.x - temp.coord.x, expect.y - temp.coord.y, expect.z - temp.coord.z);
        if (abs(to_target) > radius_) return;
        to_target /= abs(to_target);
		point_3d cur_speed;
        if (abs(temp.speed) != 0)
		{
            cur_speed = temp.speed /= abs (temp.speed);
		}
        point_3d new_force = - to_target - cur_speed;
        obj->full_force(new_force);
    }

    behavior_evade_rad::behavior_evade_rad(boost::shared_ptr<object::object_mod> target, double r)
    {
        target_ = target;
        radius_ = r;
    }

    behavior_evade_rad::~behavior_evade_rad()
    {
    }

    

    point_3d interpolation(boost::shared_ptr<object::object_mod>  target, boost::shared_ptr<object::dynamic_object>  obj)
    {
        state target_state = target->get_state(); //UNDONE
        return target_state.coord;
    }

} //behavior
#include <objects/dynamic_object.h>

using namespace std;

namespace object
{
        void dynamic_object::init(point_3d new_coord, point_3d new_speed, point_3d new_force, double new_max_speed, double new_max_force, double new_mass, double new_radius)
        {
            coord = new_coord;
            speed = new_speed;
            force = new_force;
            max_speed = new_max_speed;
            max_force = new_max_force;
            mass = new_mass;
            radius = new_radius;
        }

        void dynamic_object::deinit()
        {

        }

        void dynamic_object::revisualise (visual_object* new_visualisation)
        {
            visualisation = new_visualisation;
        }

        state dynamic_object::get_state()
        {
            state result(coord, speed);
            return result;
        }

        state_vis dynamic_object::get_state_vis()
        {
            state_vis result(coord);
            return result;
        }

        void dynamic_object::update()
        {
            speed += force;
            if (abs(speed) > max_speed)
            {
                double r_coef = abs(speed) / max_speed;
                speed /= r_coef;
            }
            coord += speed;
        }

        void dynamic_object::reg()
        {

        }

        void dynamic_object::unreg()
        {

        }

        void dynamic_object::set_force(point_3d new_force)
        {
            force = new_force;
            if (abs(force) > max_force)
            {
                double r_coef = abs(force) / max_force;
                force /= r_coef;
            }
        }


        dynamic_object::dynamic_object()
            : coord(0,0,0)
            , speed(0,0,0)
            , force(0,0,0)
            , max_speed(0)
            , max_force(0)
            , mass(0)
            , radius(0)
            , visualisation(0)
        {

        }
        dynamic_object::~dynamic_object()
        {

        }
} //objects

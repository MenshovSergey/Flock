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
            visualisation->giveown(this);
        }

        state dynamic_object::get_state()
        {
            state result(coord, speed);
            return result;
        }

        state_vis dynamic_object::get_state_vis()
        {
            state_vis result(coord);
            double r = sqrt(speed.x * speed.x + speed.y * speed.y + speed.z * speed.z);
            result.psi = asin(speed.z / r);
            r =  sqrt(speed.x * speed.x + speed.y * speed.y);
            result.phi = acos(speed.x / r);
            if (speed.y < 0)
            {
                result.phi = -result.phi;
            }
            return result;
        }

        int dynamic_object::get_type()
        {
            return obj_type;
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

        void dynamic_object::reg(object_mod* new_manager)
        {
            new_manager->reg(this);
        }

        void dynamic_object::unreg(object_mod* new_manager)
        {
            new_manager->unreg(this);
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

        void dynamic_object::full_force(point_3d dir_force)
        {
            force = dir_force / abs(dir_force) * max_force;
        }


        dynamic_object::dynamic_object(int object_type)
            : coord(0,0,0)
            , speed(0,0,0)
            , force(0,0,0)
            , max_speed(0)
            , max_force(0)
            , mass(0)
            , radius(0)
            , visualisation(0)
            , obj_type(object_type)
        {

        }
        dynamic_object::~dynamic_object()
        {

        }
} //objects

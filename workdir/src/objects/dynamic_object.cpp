#include <objects/dynamic_object.h>
#include "typedef/typedef.h"
#include "boost/weak_ptr.hpp"
using namespace std;

namespace object
{
        void dynamic_object::init(point_3d new_coord, point_3d new_speed, point_3d new_force, double new_max_speed, 
			double new_max_force, double new_max_rot, double new_mass, double new_radius)
        {
            coord = new_coord;
            speed = new_speed;
            force = new_force;
            max_speed = new_max_speed;
            max_force = new_max_force;
            max_rot = new_max_rot;
            phi = 0;
            psi = 0;
            rot_phi = 0;
            rot_psi = 0;
            mass = new_mass;
            radius = new_radius;
        }

        void dynamic_object::deinit()
        {

        }

        void dynamic_object::revisualise (boost::shared_ptr<visual_object> new_visualisation)
        {
            visualisation = new_visualisation;
			//visualisation->giveown(boost::make_shared<object::dynamic_object>(*this));

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

            result.phi = phi;
            result.psi = psi;
            return result;
		}

        int dynamic_object::get_type()
        {
            return obj_type;
        }

        void dynamic_object::update()
        {
            truncate_force();

            force = prev_force + (force - prev_force) / 10;

			speed += force;
            if (abs(speed) > max_speed)
            {
                double r_coef = abs(speed) / max_speed;
                speed /= r_coef;
            }
            coord += speed;

            double target_phi;
            double target_psi;

            if (abs(speed) == 0)
			{
				target_phi = 0;
				target_psi = 0;
                rot_phi = 0;
                rot_psi = 0;
			}
            else
            {
                double r = sqrt(speed.x * speed.x + speed.y * speed.y + speed.z * speed.z);
                double sgn = 1;
                target_psi = asin(speed.z / r);                  
                r =  sqrt(speed.x * speed.x + speed.y * speed.y);
                target_phi = acos(speed.x / r);
                if (speed.y < 0)
                {
                    target_phi = -target_phi;
                }
          
                if (target_phi > phi + M_PI)
                {
                    sgn = -1;
                }

                if (target_phi < phi - M_PI)
                {
                    sgn = -1;
                }

                r = sqrt((target_phi - phi) * (target_phi - phi) + (target_psi - psi) * (target_psi - psi));

                /*rot_phi = rot_phi + sgn * (target_phi - phi) / r * max_rot * abs(speed) / max_speed;
                if (abs(rot_phi) > abs (target_phi - phi))
                {
                    rot_phi = target_phi - phi;
                }
                rot_psi = rot_psi + sgn * (target_psi - psi) / r * max_rot * abs(speed) / max_speed;
                if (abs(rot_psi) > abs (target_psi - psi))
                {
                    rot_psi = target_psi - psi;
                } */

                rot_phi = sgn * (target_phi - phi)/10;
                rot_psi = (target_psi - psi)/10;
                

            }
            psi += rot_psi;
            phi += rot_phi;

            if (psi > M_PI / 2)
            {
                psi = M_PI / 2;
                rot_psi = 0;
            }
            if (psi < -M_PI / 2)
            {
                psi = -M_PI / 2;
                rot_psi = 0;
            }
            if (phi > M_PI)
            {
                phi -= M_PI * 2;
            }
            if (phi < - M_PI)
            {
                phi += M_PI * 2;
            }

            prev_force = force;

			force.x = 0;
			force.y = 0;
			force.z = 0;
        }

		void dynamic_object::truncate_force()
		{
			if (abs(force) > max_force)
            {
                double r_coef = abs(force) / max_force;
                force /= r_coef;
            }
		}

		void dynamic_object::add_force(point_3d new_force)
		{
			force += new_force;
		}

        void dynamic_object::reg(boost::shared_ptr<object_mod> new_manager)
        {
			//boost::dynamic_pointer_cast<test_ii>(i_ptr); 
            //new_manager->reg(this);
			//new_manager->reg(
			//new_manager->reg(
			//new_manager->reg(boost::make_shared<object::dynamic_object>(*this));
			assert(0);
        }

        void dynamic_object::unreg(boost::shared_ptr<object_mod> new_manager)
        {
			//new_manager->unreg(this);
			//new_manager->unreg(boost::make_shared<object::dynamic_object>(*this));
            //boost::weak_ptr a;
			assert(0);
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
            add_force(dir_force / abs(dir_force) * max_force);
        }

        void dynamic_object::set_flock (flock * new_parent)
        {
            parent = new_parent;
        }

        flock * dynamic_object::parent_flock()
        {
            return parent;
        }

                                    
        dynamic_object::dynamic_object(int object_type)
            : coord(0,0,0)
            , speed(0,0,0)
            , force(0,0,0)
            , max_speed(0)
            , max_force(0)
            , mass(0)
            , radius(0)
            , parent(0)
            //, visualisation(0)
            , obj_type(object_type)
        {

        }
        dynamic_object::~dynamic_object()
        {

        }
} //objects

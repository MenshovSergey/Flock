#include<objects/visual_object.h>
using namespace std;

namespace
{
    void count_radial_coord(point_3d coord, double & r, double & phi, double & psi)
    {
            r =  sqrt(coord.x * coord.x + coord.y * coord.y);
            if (r > 0)
            {
                phi = acos(coord.x / r);
            }
            else
            {
                phi = 0;
            }
            if (coord.y < 0)
            {
                phi = -phi;
            }
            r = sqrt(coord.x * coord.x + coord.y * coord.y + coord.z * coord.z);
            psi= asin(coord.z / r);
    }
}


namespace object
{
        void visual_object::init(point_3d new_coord)
        {
            coord = new_coord;
        }
        void visual_object::deinit()
        {

        }

        void visual_object::change_vis(bool is_vis)
        {
            is_visible = is_vis;
        }

        void visual_object::change_rot(bool is_rot)
        {
            is_rotating = is_rot;
        }

        void visual_object::giveown(object_mod *  const new_owner)
        {
            owner = new_owner;
        }

        look visual_object::render()
        {
            look result(model_vis);
            if (!is_visible) // object is invisible/not existent
            {
                result.is_visible = false;
                return result;
            }

            result.is_visible = true;
            result.coord = coord;

            if (is_rotating)
            {
                look temp(model_vis);

                double t_r;
                double t_phi;
                double t_psi;

                count_radial_coord(model_vis.v3, t_r, t_phi, t_psi); 

                temp.v1.x = result.v1.x * cos(-t_phi) - result.v1.y * sin(-t_phi);
                temp.v1.y = result.v1.x * sin(-t_phi) + result.v1.y * cos(-t_phi); 
                temp.v1.z = result.v1.z * cos(psi) + temp.v1.x * sin(psi);
                temp.v1.x = temp.v1.x * cos(psi) - result.v1.z * sin(psi);


                temp.v2.x = result.v2.x * cos(-t_phi) - result.v2.y * sin(-t_phi);
                temp.v2.y = result.v2.x * sin(-t_phi) + result.v2.y * cos(-t_phi); 
                temp.v2.z = result.v2.z * cos(psi) + temp.v2.x * sin(psi);
                temp.v2.x = temp.v2.x * cos(psi) - result.v2.z * sin(psi);


                temp.v3.x = result.v3.x * cos(-t_phi) - result.v3.y * sin(-t_phi);
                temp.v3.y = result.v3.x * sin(-t_phi) + result.v3.y * cos(-t_phi); 
                temp.v3.z = result.v3.z * cos(psi) + temp.v3.x * sin(psi);
                temp.v3.x = temp.v3.x * cos(psi) - result.v3.z * sin(psi);
            

                temp.v4.x = result.v4.x * cos(-t_phi) - result.v4.y * sin(-t_phi);
                temp.v4.y = result.v4.x * sin(-t_phi) + result.v4.y * cos(-t_phi); 
                temp.v4.z = result.v4.z * cos(psi) + temp.v4.x * sin(psi);
                temp.v4.x = temp.v4.x * cos(psi) - result.v4.z * sin(psi);


                t_phi += phi;

                result.v1.x = temp.v1.x * cos(t_phi) - temp.v1.y * sin(t_phi);
                result.v1.y = temp.v1.y * cos(t_phi) + temp.v1.x * sin(t_phi);
                result.v1.z = temp.v1.z;

                result.v2.x = temp.v2.x * cos(t_phi) - temp.v2.y * sin(t_phi);
                result.v2.y = temp.v2.y * cos(t_phi) + temp.v2.x * sin(t_phi);
                result.v2.z = temp.v2.z;

                result.v3.x = temp.v3.x * cos(t_phi) - temp.v3.y * sin(t_phi);
                result.v3.y = temp.v3.y * cos(t_phi) + temp.v3.x * sin(t_phi);
                result.v3.z = temp.v3.z;

                result.v4.x = temp.v4.x * cos(t_phi) - temp.v4.y * sin(t_phi);
                result.v4.y = temp.v4.y * cos(t_phi) + temp.v4.x * sin(t_phi);
                result.v4.z = temp.v4.z;
            }

            /*count_radial_coord(model_vis.v4, t_r, t_phi, t_psi); 
            t_phi += phi;
            t_psi += psi;
            result.v4.x = t_r * cos(t_phi) * cos(t_psi);
            result.v4.y = t_r * sin(t_phi) * cos(t_psi);
            result.v4.z = t_r * sin(t_psi);    */        

            return result;
            //^^TEMP CODE
            /*
             GET LOOK;
             MOVE IT BY COORD;
             TURN IT BY ORIENTATION;
             PUT IT ON A SCREEN;
            */

        }

        void visual_object::update()
        {
            if (owner == 0) return;
            state_vis temp = owner->get_state_vis();
            coord = temp.coord;
			phi = temp.phi;
			psi = temp.psi;
        }

        void visual_object::move(point_3d new_coord)
        {
            coord = new_coord;
        }

        visual_object::visual_object(look new_model)
            : coord(0,0,0)
            , model_vis(new_model)
            , phi(0)
			, psi(0)
            , is_visible(0)
            , is_rotating(1)
            , owner(0)
        {
        }

        visual_object::~visual_object()
        {

        }

}

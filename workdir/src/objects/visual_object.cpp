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

            double t_r;
            double t_phi;
            double t_psi;
            count_radial_coord(model_vis.v1, t_r, t_phi, t_psi); 
            t_phi += phi;
            t_psi += psi;
            result.v1.x = t_r * cos(t_phi) * cos(t_psi);
            result.v1.y = t_r * sin(t_phi) * cos(t_psi);
            result.v1.z = t_r * sin(t_psi);

            count_radial_coord(model_vis.v2, t_r, t_phi, t_psi); 
            t_phi += phi;
            t_psi += psi;
            result.v2.x = t_r * cos(t_phi) * cos(t_psi);
            result.v2.y = t_r * sin(t_phi) * cos(t_psi);
            result.v2.z = t_r * sin(t_psi);

            count_radial_coord(model_vis.v3, t_r, t_phi, t_psi); 
            t_phi += phi;
            t_psi += psi;
            result.v3.x = t_r * cos(t_phi) * cos(t_psi);
            result.v3.y = t_r * sin(t_phi) * cos(t_psi);
            result.v3.z = t_r * sin(t_psi);

            count_radial_coord(model_vis.v4, t_r, t_phi, t_psi); 
            t_phi += phi;
            t_psi += psi;
            result.v4.x = t_r * cos(t_phi) * cos(t_psi);
            result.v4.y = t_r * sin(t_phi) * cos(t_psi);
            result.v4.z = t_r * sin(t_psi);            

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
            , is_visible(0)
			, phi(0)
			, psi(0)
        {
        }

        visual_object::~visual_object()
        {

        }

}

#include<objects/visual_object.h>
using namespace std;

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

        void visual_object::giveown(object_mod * const new_owner)
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
            result.v1.x = model_vis.v1.x * cos(psi) - model_vis.v1.z * sin(psi);
            result.v1.y = model_vis.v1.y * cos(phi) + model_vis.v1.x * sin(phi);
            result.v1.z = model_vis.v1.z * cos(psi) + model_vis.v1.x * sin(psi);

            result.v2.x = model_vis.v2.x * cos(psi) - model_vis.v2.z * sin(psi);
            result.v2.y = model_vis.v2.y * cos(phi) + model_vis.v2.x * sin(phi);
            result.v2.z = model_vis.v2.z * cos(psi) + model_vis.v2.x * sin(psi);

            result.v3.x = model_vis.v3.x * cos(psi) - model_vis.v3.z * sin(psi);
            result.v3.y = model_vis.v3.y * cos(phi) + model_vis.v3.x * sin(phi);
            result.v3.z = model_vis.v3.z * cos(psi) + model_vis.v3.x * sin(psi);

            result.v4.x = model_vis.v4.x * cos(psi) - model_vis.v4.z * sin(psi);
            result.v4.y = model_vis.v4.y * cos(phi) + model_vis.v4.x * sin(phi);
            result.v4.z = model_vis.v4.z * cos(psi) + model_vis.v4.x * sin(psi);
           
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

        visual_object::visual_object()
            : coord(0,0,0)
            , model_vis()
            , is_visible(0)
        {
            model_vis.v1.x = -0.5;
            model_vis.v2.x = 0.5;
            model_vis.v3.y = 3.;
            model_vis.v4.z = 0.5;
        }

         visual_object::visual_object(look new_model)
            : coord(0,0,0)
            , model_vis(new_model)
            , is_visible(0)
        {
        }

        visual_object::~visual_object()
        {

        }

}

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

        void visual_object::giveown(object_mod * const new_owner)
        {
            owner = new_owner;
        }
        void visual_object::render()
        {
            if (!is_visible) // object is invisible/not existent
            {
                return;
            }

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

        }

        visual_object::~visual_object()
        {

        }

}

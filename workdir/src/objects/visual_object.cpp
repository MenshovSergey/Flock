#include<objects/visual_object.h>

using namespace std;

namespace object
{
        void visual_object::init()
        {

        }
        void visual_object::deinit()
        {

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

        }

        void visual_object::reg()
        {

        }

        void visual_object::unreg()
        {

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

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
            result.coord = coord;
            //TEMP CODE
            /*int h = 25;
            int w = 60;
            char mesh = '+';
            int pos_y = static_cast<int>(coord.y);
            int pos_x = static_cast<int>(coord.x);
            if ((pos_x < 0) || (pos_y < 0) || (pos_x >= w) || (pos_y >= h))
            {
                mesh = '.';
            }
            for (int j = 0; j < pos_y; ++j)
            {
                cout << "\n";
            }
            for (int k = 0; k < pos_x; ++k)
            {
                cout << " ";
            }
            cout << mesh;
            cout << "\n";
            for (int j = pos_y + 1; j < h; ++j)
            {
                cout << "\n";
            }*/

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

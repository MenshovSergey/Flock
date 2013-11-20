#include <objects/static_object.h>

using namespace std;

namespace object
{
        void static_object::init(point_3d new_coord, double new_radius)
        {
            coord = new_coord;
            radius = new_radius;
        }
        void static_object::deinit()
        {

        }
        state static_object::get_state()
        {
            state result;
            result.coord = coord;
            return result;
        }

        int static_object::get_type()
        {
            return obj_type;
        }

        state_vis static_object::get_state_vis()
        {
            state_vis result;
            return result;
        }
        void static_object::update()
        {
            return;
        }
        void static_object::reg(object_mod* new_manager)
        {

        }
        void static_object::unreg(object_mod* new_manager)
        {

        }


        static_object::static_object(int object_type)
            : coord(0,0,0)
            , radius(0)
            , obj_type(object_type)
        {

        }
        static_object::~static_object()
        {

        }
} //objects

#include <management/manager_flocks.h>

using namespace std;

namespace object
{
        void manager_flocks::init(double new_radius)
        {
            radius = new_radius;
        }

        void manager_flocks::deinit()
        {

        }

        state manager_flocks::get_state()
        {
            state result;
            return result;
        }

        int manager_flocks::get_type()
        {
            return obj_type;
        }

        state_vis manager_flocks::get_state_vis()
        {
            state_vis result;
            return result;
        }

        void manager_flocks::update()
        {
            size_t obj_size = objects.size();
            size_t f_size = flocks.size();
            vector<point_3d> flock_coords;
            for (size_t j = 0; j < f_size; ++j)
            {
                flock_coords.push_back(flocks[j]->get_state_vis().coord);
            }

            for (size_t i = 0; i < obj_size; ++i)
            {
                point_3d coord = objects[i]->get_state_vis().coord;
                double r = abs(flocks[0]->get_state_vis().coord - coord);
                size_t iter = 0;
                dynamic_object * cur = dynamic_cast<dynamic_object *> (objects[i].get());

                for (size_t j = 0; j < f_size; ++j)
                {
                    if (abs(flock_coords[j] - coord) < r)
                    {
                        r = abs(flock_coords[j] - coord);
                        iter = j;
                    }
                }
                if (flocks[iter].get() != cur->parent_flock())
                {
                    if (cur->parent_flock() != NULL)
                    {
                        (cur->parent_flock())->unreg(objects[i]);
                    }
                    flocks[iter]->reg(objects[i]);
                }
            }
        }

        void manager_flocks::reg(boost::shared_ptr<object_mod> new_object)
        {
            objects.push_back(new_object);
        }

        void manager_flocks::unreg(boost::shared_ptr<object_mod> new_object)
        {

        }

        void manager_flocks::reg_f(boost::shared_ptr<flock> new_flock)
        {
            flocks.push_back(new_flock);
        }

        manager_flocks::manager_flocks(int object_type)
            : radius(0)
            , obj_type(object_type)
            , flocks()
            , objects(0)
        {
        }

        manager_flocks::~manager_flocks()
        {
        }
} //object

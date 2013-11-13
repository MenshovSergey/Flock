#include <management/manager.h>
#include <objects/dynamic_object.h>
#include <cassert>

using namespace std;
namespace object
{
        state manager::get_state ()
        {
            state res; //manager has no state
            return res;
        }

        state_vis manager::get_state_vis ()
        {
            state_vis res; //manager has no state
            return res;
        }

        int manager::get_type()
        {
            return obj_type;
        }

        void manager::update ()
        {
            b_func.update(registered, controlled);
        }

        void manager::reg (object_mod* new_object)
        {
            registered.push_back (new_object);
            ++reg_size;
            try
            {
                controls * t_cont = dynamic_cast<controls *>(new_object);
                if (t_cont != 0)
                {
                    controlled.insert(make_pair(new_object, t_cont));  // IS THIS CORRECT?!
                    ++cont_size;
                }
            }
            catch (exception& e)
            {
            }
        }
        void manager::unreg (object_mod*)
        {
            assert (0);
        }
        void      manager::init (behavior::behavior_old new_behaviour)
        {
            b_func = new_behaviour;
        }
        void      manager::deinit ()
        {

        }
        manager::manager (int object_type)
            : registered()
            , controlled()
            , reg_size(0)
            , cont_size(0)
            , b_func(0)
            , obj_type(object_type)
        {
        }
        manager::~manager()
        {

        }
}
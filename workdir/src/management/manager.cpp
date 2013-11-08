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
                controlled.insert(make_pair(new_object, dynamic_cast<controls *>(new_object)));  // IS THIS CORRECT?!
                ++cont_size;
            }
            catch (exception& e)
            {
            }
        }
        void manager::unreg (object_mod*)
        {
            assert (0);
        }
        void      manager::init (behaviour::behaviour new_behaviour)
        {
            b_func = new_behaviour;
        }
        void      manager::deinit ()
        {

        }
        manager::manager ()
            : registered()
            , controlled()
            , reg_size(0)
            , cont_size(0)
            , b_func(0)
        {
        }
        manager::~manager()
        {

        }
}
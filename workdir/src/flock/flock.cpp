#include "flock/flock.h"

using namespace std;
namespace object
{

state flock::get_state ()
{
    state temp;
    return temp;
}

state_vis flock::get_state_vis ()
{
    state_vis temp;
    return temp;
}

int flock::get_type ()
{
    return obj_type;
}

void flock::update ()
{
    for (int i = 0; i < o_size; ++i)
    {
        for (int j = 0; j < b_size; ++j)
        {
            behaviors[j]->apply(objects[i]);
        }
    }
}

void flock::reg (boost::shared_ptr<object_mod> new_object)
{	
    objects.push_back(boost::dynamic_pointer_cast<dynamic_object>(new_object));
    ++o_size;
}

void flock::unreg (boost::shared_ptr<object_mod> new_object)
{

}

void flock::add_b (boost::shared_ptr<behavior::behavior_base> new_behavior)
{
    behaviors.push_back(new_behavior);
    ++b_size;
}

 vector<boost::shared_ptr<object_mod>> flock::get_members()
 {
     vector<boost::shared_ptr<object_mod>> result;
     size_t size = objects.size();
     for (size_t i = 0; i < size; ++i)
     {
         result.push_back(objects[i]);
     }
     return result;
 }

void flock::rem_b ()
{

}

flock::flock (int object_type)
    : objects()
    , o_size(0)
    , behaviors()
    , b_size(0)
{
}

flock::~flock ()
{
}

} //object

#include <behavior/behavior.h>

using namespace std;
namespace behavior
{
    behavior_old::behavior_old(void (*new_func)(std::vector<object::object_mod*>const &, std::map<object::object_mod*, object::controls*>&))
    {
        func = new_func;
    }
    
    behavior_old::~behavior_old()
    {

    }

    void behavior_old::update(std::vector<object::object_mod*>& objects, std::map<object::object_mod*, object::controls*>& controls)
    {
        func(objects, controls);
    }
    void behavior_old::apply(object::dynamic_object*)
    {
        return;
    }
}

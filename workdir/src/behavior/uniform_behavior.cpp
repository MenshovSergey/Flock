#include <behavior/uniform_behavior.h>

namespace behavior
{

    uniform_behavior::uniform_behavior(void (*new_func)(object::dynamic_object*))
    {
        func = new_func;
    }

    uniform_behavior::~uniform_behavior()
    {

    }

    void uniform_behavior::apply (object::dynamic_object* obj)
    {
        func(obj);
    }
}
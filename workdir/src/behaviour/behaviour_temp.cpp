#pragma once
#include <behaviour/behaviour.h>

using namespace std;
namespace behaviour
{
    behaviour::behaviour(void (*new_func)(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&))
    {
        func = new_func;
    }
    
    behaviour::~behaviour()
    {

    }

    void behaviour::update(std::vector<object::object_mod*>& objects, std::map<object::object_mod*, object::controls*>& controls)
    {
        func(objects, controls);
    }
    void behaviour::update(object::dynamic_object*)
    {
        return;
    }
}

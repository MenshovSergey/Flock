#pragma once
#include <objects/object_mod_base.h>
#include <objects/dynamic_object.h>
#include <vector>
#include <map>

namespace behaviour
{

struct behaviour
{
         behaviour(void (*new_func)(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&));
         ~behaviour();

	void update(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&);
    void update(object::dynamic_object*);

    private:
        void (*func)(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&);
};

}

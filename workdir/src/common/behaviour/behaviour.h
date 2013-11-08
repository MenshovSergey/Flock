#pragma once
#include <objects/object_mod_base.h>
#include <vector>
#include <map>

namespace behaviour
{

struct behaviour
{
         behaviour(void (*new_func)(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&));
         ~behaviour();

	void update(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&);

    private:
        void (*func)(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&);
};

}

#pragma once
#include <behavior/behavior_base.h>
#include <objects/object_mod_base.h>
#include <objects/dynamic_object.h>
#include <vector>
#include <map>

namespace behavior
{

class behavior_old: public behavior_base
{
    public:
         behavior_old(void (*new_func)(std::vector<object::object_mod*>const &, std::map<object::object_mod*, object::controls*>&));
         ~behavior_old();

	void update(std::vector<object::object_mod*>&, std::map<object::object_mod*, object::controls*>&);
    void apply(object::dynamic_object*);
    private:
        void (*func)(std::vector<object::object_mod*> const&, std::map<object::object_mod*, object::controls*>&);
};

}

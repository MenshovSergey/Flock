#pragma once
#include <behavior/behavior_base.h>
#include <objects/object_mod_base.h>
#include <objects/dynamic_object.h>
#include <vector>
#include <map>

#include "typedef/typedef.h"

namespace behavior
{

class behavior_old: public behavior_base
{
    public:
         behavior_old(void (*new_func)(std::vector < boost::shared_ptr < object :: object_mod> >const &, 
			 std::map< boost::shared_ptr <object::object_mod> , boost::shared_ptr<object::controls>>&));
         ~behavior_old();

    void update(std::vector< boost::shared_ptr< object :: object_mod> >&, std::map<boost::shared_ptr <object::object_mod> , 
		boost::shared_ptr<object::controls>>&);
    void apply(boost::shared_ptr<object::dynamic_object>);
    private:
        void (*func)(std::vector<boost::shared_ptr<object::object_mod>> const&, std::map<boost::shared_ptr <object::object_mod> , 
		boost::shared_ptr<object::controls>>&);
};

}

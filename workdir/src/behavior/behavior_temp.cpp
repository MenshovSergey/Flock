#include <behavior/behavior.h>
#include "typedef/typedef.h"
using namespace std;
namespace behavior
{
    behavior_old::behavior_old(void (*new_func)(std::vector<boost::shared_ptr<object::object_mod> >const &, 
		std::map<boost::shared_ptr<object::object_mod>, boost::shared_ptr<object::controls>>&))
    {
        func = new_func;
    }
    
    behavior_old::~behavior_old()
    {

    }

    void behavior_old::update (std::vector<boost::shared_ptr<object::object_mod>>& objects, std::map<boost::shared_ptr<object::object_mod>, 
		boost::shared_ptr<object::controls>>& controls)
    {
        func(objects, controls);
    }
    void behavior_old::apply(boost::shared_ptr<object::dynamic_object>)
    {
        return;
    }
}

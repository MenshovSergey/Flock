#pragma once
#include <objects/object_base.h>

namespace behaviour
{

struct behaviour
{
         behaviour();
         ~behaviour();

	void update(object::controls*  controlled);
};

}

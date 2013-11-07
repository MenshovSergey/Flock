#pragma once
#include "object_base.h"

namespace object
{

struct object_vis
    : info_vis
    , semantic
    , manipulators
{

    virtual ~object_vis() {};
};

} //object

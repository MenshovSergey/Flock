#pragma once
#include "object_base.h"

namespace object
{

struct object_vis
    : public info_vis
    , public semantic
    , public manipulators
{

    virtual ~object_vis() {};
};

} //object

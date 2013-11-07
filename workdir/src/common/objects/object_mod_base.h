#pragma once
#include "object_base.h"

namespace object
{

struct object_mod
    : info_mod
    , semantic
{

    virtual ~object_mod() {};
};

} //object

#pragma once
#include "object_base.h"

namespace object
{

struct object_mod
    : info_mod
    , semantic
{
    virtual void    reg        (object_mod*) = 0;
    virtual void    unreg      (object_mod*) = 0;

    virtual ~object_mod() {};
};

} //object

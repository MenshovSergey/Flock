#pragma once
#include <objects/object_base.h>

namespace object
{

struct object_mod
    : public info_mod
    , public semantic
{
    virtual void    reg        (object_mod*) = 0;
    virtual void    unreg      (object_mod*) = 0;

    virtual ~object_mod() {};
};

} //object

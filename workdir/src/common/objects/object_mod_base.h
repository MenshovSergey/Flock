#include "object_base.h"

namespace object
{

struct object_mod
    : construction
    , info_mod
    , semantic
{

    virtual ~object_mod() {};
}

} //object

#include "object_base.h"

namespace object
{

struct object_vis
    : construction
    , info_vis
    , semantic
    , manipulators
{

    virtual ~object_vis() {};
};

} //object

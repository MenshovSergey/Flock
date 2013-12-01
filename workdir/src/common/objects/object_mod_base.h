#pragma once
#include <objects/object_base.h>
#include "typedef/typedef.h"
namespace object
{

struct object_mod
    : public info_mod
    , public semantic
{
    //virtual void    reg        (myPtr<object_mod>::my_ptr) = 0;
	virtual void    reg        (boost::shared_ptr<object_mod>) = 0;

    //virtual void    unreg      (myPtr<object_mod>::my_ptr) = 0;

	virtual void    unreg      (boost::shared_ptr<object_mod>) = 0;

    virtual ~object_mod() {};
};

} //object



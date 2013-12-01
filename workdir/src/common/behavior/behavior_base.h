#pragma once
#include <objects/dynamic_object.h>
#include "typedef/typedef.h"
namespace behavior
{

struct behavior_base
{
    virtual void apply          (boost::shared_ptr<object::dynamic_object>) = 0;
    virtual      ~behavior_base (){};
};

} //behavior
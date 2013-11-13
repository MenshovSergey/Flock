#pragma once
#include <objects/dynamic_object.h>
namespace behavior
{

struct behavior_base
{
    virtual void apply          (object::dynamic_object * obj) = 0;
    virtual      ~behavior_base (){};
};

} //behavior
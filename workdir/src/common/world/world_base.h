#pragma once
#include <objects/object_mod_base.h>
#include <vector>

namespace world
{

struct construction
{
    virtual void add           () = 0;
    virtual void remove        () = 0;
    virtual      ~construction () {};
};

struct info
{
    virtual object::object_mod &               const access  () = 0;
    virtual std::vector<object::object_mod*> & const content () = 0;
    virtual                                          ~info () {};
};

struct semantic
{
    virtual void update   () = 0;
    virtual void obj_sort () = 0; //i suppose we would update managers before objects and so on;
}

} //world
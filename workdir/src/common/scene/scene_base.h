#pragma once
#include<objects/object_vis_base.h>

namespace scene
{

struct construction
{
    virtual void add            (object::object_vis & const) = 0;
    virtual void remove         (size_t) = 0;
    virtual      ~construction  () {};

};

struct info
{
    virtual object::object_vis &               const access  (size_t) = 0;
    virtual std::vector<object::object_vis*> & const content () = 0;
    virtual                                          ~info () {};
};

struct semantic
{
    virtual void update     () = 0;
    virtual void render     () = 0;
    virtual      ~semantic  () {};
};

} //scene

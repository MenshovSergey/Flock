#pragma once
#include<objects/object_vis_base.h>
#include "typedef/typedef.h"
namespace scene
{

struct construction
{
    virtual void add            (boost::shared_ptr<object::object_vis> ) = 0;
    virtual void remove         (size_t) = 0;
    virtual      ~construction  () {};

};

struct info
{
    virtual object::object_vis const &               access  (size_t) = 0;
    virtual std::vector<boost::shared_ptr<object::object_vis>>const &  content () = 0;
    virtual                                          ~info () {};
};

struct semantic
{
    virtual void update     () = 0;
    virtual void render     () = 0;
    virtual      ~semantic  () {};
};

} //scene

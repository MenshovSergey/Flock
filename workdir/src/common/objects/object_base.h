#pragma once
#include "containers/state.h"
#include "containers/state_vis.h"
#include "containers/look.h"
#include <geometry/point_3d.h>
#include <vector>


namespace object
{
	//all method was = 0;
struct info_mod
{
    virtual state     get_state     () = 0;
    virtual state_vis get_state_vis () = 0;
    virtual int       get_type      () = 0;
    virtual           ~info_mod     () {}
};

struct info_vis
{
    virtual look  render  () = 0 ;
    virtual       ~info_vis () {}
};

struct semantic
{
    virtual void  update    () = 0 ;
    virtual       ~semantic () {}
};

struct controls
{
    virtual void set_force (point_3d new_force) = 0;
	virtual void add_force (point_3d new_force) = 0;
    virtual void full_force(point_3d dir_force) = 0;
    virtual      ~controls () {}
};

struct manipulators
{
    virtual void move(point_3d) = 0;
    virtual      ~manipulators() {}
};

} //object

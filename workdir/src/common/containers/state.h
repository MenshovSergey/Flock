#pragma once
#include<geometry/point_3d.h>

struct state 
{
    point_3d coord;
	point_3d speed;
    //behavior_state behavior;
    //quaternion for orientation
    state()
        : coord()
        , speed()
    {
    }
    state(point_3d new_coord, point_3d new_speed)
        : coord(new_coord)
        , speed(new_speed)
    {
    }

};

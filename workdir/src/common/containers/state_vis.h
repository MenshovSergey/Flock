#pragma once
#include<geometry/point_3d.h>

struct state_vis
{
	point_3d coord;

    state_vis()
        : coord()
    {
    }

    state_vis(point_3d new_coord)
        : coord(new_coord)
    {
    }
    //quaternion for orientation
};
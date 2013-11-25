#pragma once
#include<geometry/point_3d.h>

struct state_vis
{
    point_3d coord;
    double phi;
    double psi;
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
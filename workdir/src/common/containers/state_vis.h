#pragma once
#include<geometry/point_3d.h>

struct state_vis
{
    point_3d coord;
    double phi;
    double psi;
    state_vis()
        : coord(0,0,0)
		, phi(0)
		, psi(0)
    {
    }

    state_vis(point_3d new_coord)
        : coord(new_coord)
		, phi(0)
		, psi(0)
    {
    }
    //quaternion for orientation
};
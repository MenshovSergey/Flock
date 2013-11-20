#pragma once
#include<geometry/point_3d.h>

struct look
{
    //here comes everything that forms visual representation of object
    double size;
    int color;
    bool is_visible;
    point_3d coord;
    point_3d v1;
    point_3d v2;
    point_3d v3;
    point_3d v4;
};
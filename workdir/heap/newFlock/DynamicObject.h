#pragma once
#include "object_base.h"

struct dynamic_object
    : object_base
{
    void add();
    void update();
    void erase();
    void move();
    State t;
    Dynamic_Object();

    int x,y,z;
};

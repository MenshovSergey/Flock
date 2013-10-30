#pragma once
#include "object_base.h"

struct static_object
	: object_base
{
    void move();
    void erase();
    void add();
    void update();
    int getX();
    int getY();
    Static_Object();
    int x;
    int y;
    int z;
};

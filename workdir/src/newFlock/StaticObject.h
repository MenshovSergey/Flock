#pragma once
#include "Object.h"

struct Static_Object :Object{

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

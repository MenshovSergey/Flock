#pragma once

#include <vector>
using namespace std;
struct Object{
    virtual void update() = 0 ;
    virtual void add() = 0 ;
    virtual void erase() = 0;
    virtual void move() = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;

};


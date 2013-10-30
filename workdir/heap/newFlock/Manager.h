#pragma once
#include "object_base.h"
#include "Flock.h"
#include <vector>

struct Manager
	: object_base
{
    virtual void update() = 0;
    void add();
    std::vector <Flock>* objects;
};

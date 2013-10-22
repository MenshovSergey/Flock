#pragma once
#include "Object.h"

struct World{
	virtual void update() = 0;
	virtual void add(Object const&) = 0;
	virtual void erase(Object const&) = 0;
	std::vector <Object>* objects_of_world;
};
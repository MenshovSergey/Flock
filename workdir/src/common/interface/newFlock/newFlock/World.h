#pragma once
#include "Object.h"

struct World{
	void update();
	void add(Object const&);
	void erase(Object const&);
	std::vector <Object>* objects_of_world;
};
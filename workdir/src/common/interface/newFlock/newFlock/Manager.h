#pragma once
#include "Object.h"
#include "Flock.h"
#include <vector>
struct Manager : Object{
	virtual void update() = 0;
	void add();
	std::vector <Flock>* objects;
};
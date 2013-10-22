#pragma once
#include <vector>
#include "World.h"

struct Object{
	virtual void update() = 0;
	virtual void add() = 0;
	virtual void erase() = 0;
	virtual void move() = 0;
	std::vector <Object>* objects;
	void add(Object const&);	
};
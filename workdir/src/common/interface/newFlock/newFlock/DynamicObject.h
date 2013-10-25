#pragma once
#include "Object.h"
#include "State.h"
struct Dynamic_Object : Object{
	void add();
	void update();
	void erase();
	void move();
	State t;
};
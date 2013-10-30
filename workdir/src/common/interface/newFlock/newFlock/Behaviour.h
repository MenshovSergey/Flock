#pragma once 
#include "Flock.h"
#include <string>

struct Behaviour: Flock {
	Behaviour (Flock*);
	std::string type;
	void update();
};
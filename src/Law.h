#pragma once
#include "Particle.h"

#include <vector>

class Law {
	public:
		virtual void run(vector<Particle*> particles) = 0;
};
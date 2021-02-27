#pragma once
#include "Particle.h"

#include <list>

class Law {
	public:
		virtual void run(list<Particle*> particles) = 0;
};
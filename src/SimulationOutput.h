#pragma once
#include "Particle.h"

#include <list>

class SimulationOutput {
	public:
		virtual void output(list<Particle*> particles) = 0;
};
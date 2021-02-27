#pragma once
#include "Particle.h"

#include <list>

class SimulationInput {
	public:
		virtual list<Particle*> input() = 0;
};
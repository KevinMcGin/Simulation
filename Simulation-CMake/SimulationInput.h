#pragma once
#include "Particle.h"

#include <vector>

class SimulationInput {
	public:
		virtual vector<Particle*> input() = 0;
};
#pragma once
#include "Particle.h"

#include <vector>

class SimulationOutput {
	public:
		virtual void output(vector<Particle*> particles) = 0;
};
#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"

#include <vector>

class SimulationInputSimple: public SimulationInput {
	public:
		virtual vector<Particle*> input();
};
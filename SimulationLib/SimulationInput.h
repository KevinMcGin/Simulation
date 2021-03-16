#pragma once
#include "Particle.cuh"

#include <vector>

class SimulationInput {
	public:
		virtual vector<Particle*> input() = 0;
};
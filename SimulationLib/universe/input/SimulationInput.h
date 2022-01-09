#pragma once
#include "particle/Particle.cuh"

#include <vector>

class SimulationInput {
	public:
		virtual vector<Particle*> input() = 0;
};
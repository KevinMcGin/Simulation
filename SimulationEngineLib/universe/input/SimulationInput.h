#pragma once
#include "particle/Particle.cuh"

#include <vector>

class SimulationInput {
	public:
		virtual std::vector<Particle*> input() = 0;
};
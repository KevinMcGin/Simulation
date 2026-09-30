#pragma once
#include "shared/particle/Particle.cuh"

#include <vector>

class SimulationInput {
public:
	virtual ~SimulationInput() = default;
	virtual std::vector<Particle*> input() = 0;
};
#pragma once
#include "Particle.cuh"

#include <vector>

class SimulationOutput {
	public:
		virtual ~SimulationOutput() {}
		virtual void output(vector<Particle*> particles, unsigned long time) = 0;
};
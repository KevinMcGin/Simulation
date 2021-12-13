#pragma once
#include "Particle.cuh"

#include <vector>

class Law {
public:
	Law();
	virtual void cpuRun(vector<Particle*>& particles) = 0;
	virtual void gpuRun(vector<Particle*>& particles) = 0;

};
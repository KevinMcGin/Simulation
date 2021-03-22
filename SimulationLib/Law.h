#pragma once
#include "Particle.cuh"

#include <vector>

class Law {
public:
	Law();
	virtual void run(vector<Particle*>& particles) = 0;
	virtual void runParallel(vector<Particle*>& particles) = 0;
	//virtual void parallelRun(UniverseGPU* universeGPU) = 0;

};
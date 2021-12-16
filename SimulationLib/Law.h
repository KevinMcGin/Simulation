#pragma once
#include "Particle.cuh"
#include "CudaWithError.cuh"

#include <vector>

class Law {
public:
	Law(string className);
	virtual void cpuRun(vector<Particle*>& particles) = 0;
	virtual void gpuRun(vector<Particle*>& particles) = 0;
protected:
	CudaWithError* cudaWithError;

};
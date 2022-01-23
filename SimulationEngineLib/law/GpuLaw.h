#pragma once
#include "particle/Particle.cuh"
#include "gpuHelper/CudaWithError.cuh"

#include <vector>

class GpuLaw {
public:
	GpuLaw(string className = "GpuLaw");
	virtual void run(Particle** td_par, int particleCount) {};
	string getClassName() { return className; }
protected:
	CudaWithError* cudaWithError;
private:
	string className = "GpuLaw";
};
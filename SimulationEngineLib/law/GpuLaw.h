#pragma once
#include "particle/Particle.cuh"
#include "gpuHelper/CudaWithError.cuh"

#include <vector>

class GpuLaw {
public:
	GpuLaw(std::string className = "GpuLaw");
	virtual void run(Particle** td_par, int particleCount) {};
	std::string getClassName() { return className; }
protected:
	CudaWithError* cudaWithError;
private:
	std::string className = "GpuLaw";
};
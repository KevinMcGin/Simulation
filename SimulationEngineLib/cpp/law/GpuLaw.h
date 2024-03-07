#pragma once
#include "shared/particle/Particle.cuh"
#include "cuda/gpuHelper/CudaWithError.cuh"

#include <vector>
#include <memory>

class GpuLaw {
public:
	GpuLaw(std::string className = "GpuLaw");
	virtual void run(Particle** td_par, int particleCount) {};
	std::string getClassName() { return className; }
protected:
	std::shared_ptr<CudaWithError> cudaWithError;
private:
	std::string className = "GpuLaw";
};
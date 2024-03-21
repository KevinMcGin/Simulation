#pragma once
#include "shared/particle/Particle.cuh"
#if defined(USE_GPU)
	#include "cuda/gpuHelper/CudaWithError.cuh"
#else
	#include "gpuMock/gpuHelper/CudaWithError.cuh"
#endif

#include <vector>
#include <memory>

class GpuLaw {
public:
	GpuLaw(std::string className);
	~GpuLaw();
	virtual void run(
		Particle** td_par, 
		int particleCount,
		unsigned int deltaTime = 1
	) {};
	protected:
		std::shared_ptr<CudaWithError> cudaWithError;
};
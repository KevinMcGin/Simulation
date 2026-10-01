#pragma once
#include "shared/precision/Real.cuh"
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
	// Deleted through this base by Law — see CpuLaw.
	virtual ~GpuLaw();
	virtual void run(
		Particle** td_par, 
		int particleCount,
		Real deltaTime = 1.0
	) {};
	protected:
		std::shared_ptr<CudaWithError> cudaWithError;
};
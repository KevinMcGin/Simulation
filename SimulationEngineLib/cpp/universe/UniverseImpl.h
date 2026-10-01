#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/universe/Universe.h"
#include "cpp/universe/input/SimulationInput.h"
#include "cpp/universe/UniverseTiming.h"
#include "shared/particle/Particle.cuh"

#if defined(USE_GPU)
	#include "cuda/gpuHelper/GpuDataController.cuh"
#else
	#include "gpuMock/gpuHelper/GpuDataController.cuh"
#endif

#include <memory>
#include <vector>

class UniverseImpl: public Universe {
public:
	UniverseImpl(
		std::vector<std::shared_ptr<Law>> laws, 
		std::shared_ptr<SimulationInput> input, 
		std::shared_ptr<SimulationOutput> output, 
		Real deltaTime, 
		unsigned long endTime,
		Usage useGpu = UNDEFINED
	);
	~UniverseImpl();
	void run() override;
	
private:
	std::unique_ptr<GpuDataController> gpuDataController;
	UniverseTiming universeTiming;
};
#pragma once
#include "cpp/universe/Universe.h"
#include "cpp/universe/input/SimulationInput.h"
#include "cuda/gpuHelper/GpuDataController.cuh"
#include "cpp/universe/UniverseTiming.h"

#include <vector>

class UniverseImpl: public Universe {
public:
	UniverseImpl(
		std::vector<std::shared_ptr<Law>> laws, 
		std::shared_ptr<SimulationInput> input, 
		std::shared_ptr<SimulationOutput> output, 
		unsigned int deltaTime, 
		unsigned long endTime,
		Usage useGpu = UNDEFINED
	);
	~UniverseImpl();
	void run() override;
	
private:
	GpuDataController* gpuDataController;
	UniverseTiming universeTiming;
};
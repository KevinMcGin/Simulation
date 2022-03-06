#pragma once
#include "universe/Universe.h"
#include "universe/input/SimulationInput.h"
#include "gpuHelper/GpuDataController.cuh"
#include "universe/UniverseTiming.h"

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
	UniverseTiming universeTiming = UniverseTiming();

	void printPercentComplete(int lawsRan, bool force = false);
	void updateSectionsTiming(std::string name);
	void printSectionsTiming();
};
#pragma once
#include "universe/Universe.h"
#include "universe/input/SimulationInput.h"
#include "gpuHelper/GpuDataController.cuh"
#include "universe/UniverseTiming.h"

#include <vector>

class UniverseImpl: public Universe {
public:
	UniverseImpl(
		vector<Law*> laws, 
		shared_ptr<SimulationInput> input, 
		shared_ptr<SimulationOutput> output, 
		unsigned int deltaTime, 
		unsigned long endTime,
		Usage use_gpu = UNDEFINED
	);
	~UniverseImpl();
	virtual void run();
	
private:
	GpuDataController* gpuDataController;
	UniverseTiming universeTiming = UniverseTiming();

	void printPercentComplete(int lawsRan, bool force = false);
	void updateSectionsTiming(string name);
	void printSectionsTiming();
};
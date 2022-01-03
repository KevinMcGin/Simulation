#pragma once
#include "Universe.h"
#include "SimulationInput.h"
#include "GpuDataController.cuh"
#include "UniverseTiming.h"

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
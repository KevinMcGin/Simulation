#pragma once
#include "Universe.h"
#include "SimulationInput.h"
#include "GpuDataController.cuh"

#include <vector>

class UniverseImpl: public Universe {
public:
	UniverseImpl(vector<Law*> laws, SimulationInput* input, SimulationOutput* output, unsigned int deltaTime, unsigned long endTime);
	~UniverseImpl();
	virtual void run();
	
private:
	double progress;
	GpuDataController* gpuDataController;

	void printPercentComplete(int lawsRan);
};
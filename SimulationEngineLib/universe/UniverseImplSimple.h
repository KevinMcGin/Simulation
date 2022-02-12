#pragma once
#include "universe/UniverseImpl.h"
#include "universe/input/SimulationInput.h"

#include <vector>

class UniverseImplSimple : public UniverseImpl {
public:
	UniverseImplSimple(
		shared_ptr<SimulationInput> input, 
		shared_ptr<SimulationOutput> output, 
		unsigned long endTime, 
		Usage useGpu = UNDEFINED
	);
};
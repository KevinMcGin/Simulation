#pragma once
#include "cpp/universe/UniverseImpl.h"
#include "cpp/universe/input/SimulationInput.h"

#include <vector>

class UniverseImplSimple : public UniverseImpl {
public:
	UniverseImplSimple(
		std::shared_ptr<SimulationInput> input, 
		std::shared_ptr<SimulationOutput> output, 
		unsigned long endTime, 
		Usage useGpu = UNDEFINED
	);
};
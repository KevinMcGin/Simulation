#pragma once
#include "UniverseImpl.h"
#include "SimulationInput.h"

#include <vector>

class UniverseImplSimple : public UniverseImpl {
public:
	UniverseImplSimple(shared_ptr<SimulationInput> input, shared_ptr<SimulationOutput> output, unsigned long endTime);
};
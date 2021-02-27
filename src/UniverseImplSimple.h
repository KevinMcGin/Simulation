#pragma once
#include "UniverseImpl.h"
#include "SimulationInput.h"
#include "NewtonGravity.h"
#include "NewtonFirstLaw.h"

#include <list>

class UniverseImplSimple : public UniverseImpl {
	public:
		UniverseImplSimple(SimulationInput* input, SimulationOutput* output, unsigned long endTime)
		: UniverseImpl({ new NewtonGravity(), new NewtonFirstLaw() }, input, output, 1, endTime) {}
};
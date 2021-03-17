﻿#pragma once
#include "UniverseImpl.cuh"
#include "SimulationInput.h"

#include <vector>

class UniverseImplSimple : public UniverseImpl {
	public:
		UniverseImplSimple(SimulationInput* input, SimulationOutput* output, unsigned long endTime);
};
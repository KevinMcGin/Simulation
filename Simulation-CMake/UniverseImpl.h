﻿#pragma once
#include "Universe.h"
#include "SimulationInput.h"
#include "NewtonGravity.h"

#include <vector>

class UniverseImpl: public Universe{
	public:
		UniverseImpl(vector<Law*> laws, SimulationInput* input, SimulationOutput* output, unsigned int deltaTime, unsigned long endTime);

		virtual void run();
};
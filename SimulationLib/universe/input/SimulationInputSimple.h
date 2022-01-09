﻿#pragma once
#include "universe/input/SimulationInput.h"
#include "particle/ParticleSimple.h"

#include <vector>

class SimulationInputSimple: public SimulationInput {
	public:
		virtual vector<Particle*> input();
};
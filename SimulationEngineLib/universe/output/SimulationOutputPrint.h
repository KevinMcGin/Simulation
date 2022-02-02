﻿#pragma once
#include "universe/output/SimulationOutput.h"

#include <vector>
#include <iostream>

class SimulationOutputPrint: public SimulationOutput {
	public:
		virtual void output(vector<Particle*> particles, unsigned long time);
};
#pragma once
#include "cpp/universe/output/SimulationOutput.h"

#include <vector>
#include <iostream>

class SimulationOutputNothing: public SimulationOutput {
public:
	void output(std::vector<Particle*> particles, unsigned long time) override;
};
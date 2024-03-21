#pragma once
#include "cpp/universe/input/SimulationInput.h"
#include "cpp/particle/ParticleSimple.h"

#include <vector>
#include <fstream>

class SimulationInputFile: public SimulationInput {
public:
	SimulationInputFile(const char* fileName);
	std::vector<Particle*> input() = 0;
protected:
	std::ifstream file;
};
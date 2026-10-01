#pragma once
#include "cpp/universe/input/SimulationInput.h"
#include "shared/particle/Particle.cuh"

#include <string>
#include <vector>

// Particles read from CSV already in memory — the body of a request, say,
// rather than a file the engine has to be given a path to. Holds the text
// by value: a request body does not outlive the handler that received it,
// and the universe reads its input after that handler has moved on.
class SimulationInputCsvText: public SimulationInput {
	public:
		explicit SimulationInputCsvText(std::string csv);
		std::vector<Particle*> input() override;
	private:
		std::string csv;
};

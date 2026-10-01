#pragma once
#include "cpp/universe/input/SimulationInput.h"
#include "shared/particle/Particle.cuh"

#include <memory>
#include <vector>

// Several inputs as one, their particles concatenated in the order given.
//
// This is what makes the engine's input sources additive rather than a
// choice between them: a generated star system, a set of particles supplied
// as CSV, and the final state of an earlier run can all seed the same
// universe.
class SimulationInputCombined: public SimulationInput {
	public:
		explicit SimulationInputCombined(std::vector<std::shared_ptr<SimulationInput>> inputs);
		std::vector<Particle*> input() override;
	private:
		std::vector<std::shared_ptr<SimulationInput>> inputs;
};

#pragma once
#include "cpp/universe/input/SimulationInput.h"
#include "cpp/particle/ParticleSimple.h"

#include <vector>

class SimulationInputSimpleLargeVelocities: public SimulationInput {
	public:
		std::vector<Particle*> input() override;
};
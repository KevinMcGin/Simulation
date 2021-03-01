#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"

#include <vector>

class SimulationInputSimple: public SimulationInput {
	public:
		virtual vector<Particle*> input() {
			return { 
				new ParticleSimple(1, 1, { 1, 0, 0}, {1, 0, 0}, {0, 0, 0 }),
				new ParticleSimple(1, 1, { 0, 1, 0}, {0, 1, 0}, {0, 0, 0 }) 
			};
		}
};
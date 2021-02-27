#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"

#include <list>

class SimulationInputSimple: public SimulationInput {
	public:
		virtual list<Particle*> input() {
			return { 
				new ParticleSimple(1, 1, { 1, 0, 0}, {1, 0, 0}, {0, 0, 0 }),
				new ParticleSimple(1, 1, { 0, 1, 0}, {0, 1, 0}, {0, 0, 0 }) 
			};
		}
};
#pragma once
#include "Particle.h"
#include "SimulationOutput.h"
#include "Law.h"

#include <list>

class Universe {
	public:
		list<Particle*> particles;
		virtual void run() = 0;

	protected:
		list<Law*> laws;
		SimulationOutput* output;
		unsigned int deltaTime;
		unsigned long endTime;
};
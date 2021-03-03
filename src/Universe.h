#pragma once
#include "Particle.h"
#include "SimulationOutput.h"
#include "Law.h"

#include <vector>

class Universe {
	public:
		~Universe() {
			delete output;
		}
		vector<Particle*> particles;
		virtual void run() = 0;

	protected:
		vector<Law*> laws;
		SimulationOutput* output;
		unsigned int deltaTime;
		unsigned long endTime;
};
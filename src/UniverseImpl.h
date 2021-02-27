#pragma once
#include "Universe.h"
#include "SimulationInput.h"
#include "NewtonGravity.h"

#include <list>

class UniverseImpl: public Universe{
	public:
		UniverseImpl(list<Law*> laws, SimulationInput* input, SimulationOutput* output, unsigned int deltaTime, unsigned long endTime) {
			particles = input->input();
			this->laws = laws;
			this->output = output;
			this->deltaTime = deltaTime;
			this->endTime = endTime;
		}

		virtual void run() {
			output->output(particles);
			for (unsigned long i = 0; i < endTime; i += deltaTime) {
				for (const auto& l : laws) {
					l->run(particles);
				}
				output->output(particles);
			}
		};
};
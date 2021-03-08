#include "UniverseImpl.h"



UniverseImpl::UniverseImpl(vector<Law*> laws, SimulationInput* input, SimulationOutput* output, unsigned int deltaTime, unsigned long endTime)
{
	particles = input->input();
	this->laws = laws;
	this->output = output;
	this->deltaTime = deltaTime;
	this->endTime = endTime;
}

void UniverseImpl::run()
{
	output->output(particles, 0);
	double progress = -1;
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		for (const auto& l : laws) {
			l->run(particles);
		}
		output->output(particles, i + 1);
		double updatedProgress = 100 * 10 * i / endTime;
		if (updatedProgress != progress) {
			progress = updatedProgress;
			cout << "\r" << progress / 10 << "%";
		}
	}
}

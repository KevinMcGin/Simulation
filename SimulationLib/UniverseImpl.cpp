#include "UniverseImpl.h"
#include<cmath>


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
	cout << "Simulation running" << endl;
	output->output(particles, 0);
	this->progress = -1;
	int lawsRan = 0;
	printPercentComplete(0);
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		for (const auto& l : laws) {
			l->run(particles);
			printPercentComplete(++lawsRan);
		}
		output->output(particles, i + 1);
	}
	cout << "Simulation complete" << endl;
}

void UniverseImpl::printPercentComplete(int lawsRan) {
	int accurary = 1000;
	double timePassed = (lawsRan/(double)laws.size()) / endTime;
	double updatedProgress =  ((int)(100 *timePassed*accurary)/(double)accurary);
	if (updatedProgress != progress) {
		progress = updatedProgress;
		cout << "\r" << progress << "%" << "     ";
	}
}


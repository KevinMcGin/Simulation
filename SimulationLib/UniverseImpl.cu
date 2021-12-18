#include "UniverseImpl.cuh"
#include<cmath>
#include "Timing.h"
#include <iostream>


UniverseImpl::UniverseImpl(vector<Law*> laws, SimulationInput* input, SimulationOutput* output, unsigned int deltaTime, unsigned long endTime) : Universe() {
	particles = input->input();
	this->laws = laws;
	this->output = output;
	this->deltaTime = deltaTime;
	this->endTime = endTime;
	if(USE_GPU == TRUE) {
		gpuDataController = new GpuDataController();
	}
}

UniverseImpl::~UniverseImpl() {
	delete gpuDataController;
}

void UniverseImpl::run() {
	cout << "Simulation running" << endl;
	cout << particles.size() << " particles" << endl;
	cout << "Frames: " << endTime << endl;
	printPercentComplete(0);
	output->output(particles, 0);
	this->progress = -1;
	int lawsRan = 0;
	bool particleDeleted = false;
	if(USE_GPU == TRUE) {
		gpuDataController->putParticlesOnDevice(particles, true);
	}
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		if(USE_GPU == TRUE) {
			if(particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
			}
		}
		particleDeleted = false;
		for (const auto& l : laws) {
			if(USE_GPU == TRUE) {
				l->gpuRun(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuRun(particles);
			}
			printPercentComplete(++lawsRan);
		}
		if(USE_GPU == TRUE) {
			gpuDataController->getParticlesFromDevice(particles);
			//TODO: do this on gpu
			//Erase particles for deletion
			for (auto it = particles.begin(); it != particles.end();) {
				if((*it)->deleted) {
					delete *it;
					it = particles.erase(it);
					particleDeleted = true;
				}
				else
					++it;
			}
		}
		output->output(particles, i + 1);
	}
	cout << endl << "Simulation complete" << endl;
}

void UniverseImpl::printPercentComplete(int lawsRan) {
	float accurary = 1000.f;
	float timePassed = (lawsRan/(float)laws.size()) / endTime;
	progress =  (100 * timePassed * accurary) / accurary;
	cout << "\r" << progress << "% " << Timing::getTime() << "            " << std::flush;
}


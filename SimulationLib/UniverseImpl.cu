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

float progresses[7] = {0, 0, 0, 0, 0, 0, 0};
int progressIndex = 0;

void UniverseImpl::run() {
	cout << "Simulation running" << endl;
	cout << particles.size() << " particles" << endl;
	cout << "Frames: " << endTime << endl;
	// printPercentComplete(0);
	output->output(particles, 0);
	this->progress = -1;
	int lawsRan = 0;
	bool particleDeleted = false;
	if(USE_GPU == TRUE) {
		Timing::setTime();
		gpuDataController->putParticlesOnDevice(particles, true);
		printPercentComplete(0);
	}
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		if(USE_GPU == TRUE) {
			if(particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
			}
		}
		particleDeleted = false;
		int j = 1;
		for (const auto& l : laws) {
			Timing::setTime();
			if(USE_GPU == TRUE) {
				l->gpuRun(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuRun(particles);
			}
			printPercentComplete(j++);
		}
		if(USE_GPU == TRUE) {
			Timing::setTime();
			gpuDataController->getParticlesFromDevice(particles);
			printPercentComplete(4);
			//TODO: do this on gpu
			//Erase particles for deletion
			Timing::setTime();
			for (auto it = particles.begin(); it != particles.end();) {
				if((*it)->deleted) {
					delete *it;
					it = particles.erase(it);
					particleDeleted = true;
				}
				else
					++it;
			}
			printPercentComplete(6);
		}
		Timing::setTime();
		output->output(particles, i + 1);
		printPercentComplete(5);
	}
	cout << endl << "Simulation complete" << endl;
}

void UniverseImpl::printPercentComplete(int lawsRan) {
	// float accurary = 1000.f;
	// float timePassed = (lawsRan/(float)laws.size()) / endTime;
	// progress = (100 * timePassed * accurary) / accurary;
	progresses[lawsRan] += Timing::getTimeSeconds();
	cout << "\r" << 
		"Collision" << ": " << progresses[1] << ", " <<
		"Gravity" << ": " << progresses[2] << ", " <<
		"First Law" << ": " << progresses[3] << ", " <<
		"Data from GPU" << ": " << progresses[4] << ", " <<
		"Deletions" << ": " << progresses[6] << ", " <<
		"Data to GPU" << ": " << progresses[0] << ", " <<
		"Data to JSON" << ": " << progresses[5] <<
		"            " << std::flush;
	// cout << "\r" << progress << "% " << Timing::getTimeWithUnit() << "            " << std::flush;
}


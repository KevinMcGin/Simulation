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

Timing timingTotal = Timing();
Timing timingSections = Timing();
float progresses[7] = {0, 0, 0, 0, 0, 0, 0};
int progressIndex = 0;

void UniverseImpl::run() {
	cout << "Simulation running" << endl;
	cout << particles.size() << " particles" << endl;
	cout << "Frames: " << endTime << endl;
	timingTotal.setTime();
	printPercentComplete(0);
	output->output(particles, 0);
	this->progress = -1;
	int lawsRan = 0;
	bool particleDeleted = false;
	if(USE_GPU == TRUE) {
		timingSections.setTime();
		gpuDataController->putParticlesOnDevice(particles, true);
		updateSectionsTiming(0);
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
			timingSections.setTime();
			if(USE_GPU == TRUE) {
				l->gpuRun(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuRun(particles);
			}
			updateSectionsTiming(j++);
			printPercentComplete(++lawsRan);
		}
		if(USE_GPU == TRUE) {
			timingSections.setTime();
			gpuDataController->getParticlesFromDevice(particles);
			updateSectionsTiming(4);
			//TODO: do this on gpu
			//Erase particles for deletion
			timingSections.setTime();
			for (auto it = particles.begin(); it != particles.end();) {
				if((*it)->deleted) {
					delete *it;
					it = particles.erase(it);
					particleDeleted = true;
				}
				else
					++it;
			}
			updateSectionsTiming(6);
		}
		timingSections.setTime();
		output->output(particles, i + 1);
		updateSectionsTiming(5);
	}
	printSectionsTiming();
	cout << endl << "Simulation complete" << endl;
}

void UniverseImpl::printPercentComplete(int lawsRan) {
	float accurary = 1000.f;
	float timePassed = (lawsRan/(float)laws.size()) / endTime;
	progress = (100 * timePassed * accurary) / accurary;
	cout << "\r" << 
		progress << "% " << timingTotal.getTimeWithUnit() << 
		"                       " << std::flush;
}

void UniverseImpl::updateSectionsTiming(int index) {
	progresses[index] += timingSections.getTimeSeconds();
}

void UniverseImpl::printSectionsTiming() {
	cout << std::endl << 
		"Collision" << ": " << progresses[1] << ", " <<
		"Gravity" << ": " << progresses[2] << ", " <<
		"First Law" << ": " << progresses[3] << ", " <<
		"Data from GPU" << ": " << progresses[4] << ", " <<
		"Deletions" << ": " << progresses[6] << ", " <<
		"Data to GPU" << ": " << progresses[0] << ", " <<
		"Data to JSON" << ": " << progresses[5] <<
		std::endl;
}


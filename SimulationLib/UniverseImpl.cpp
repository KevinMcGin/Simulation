#include "UniverseImpl.h"
#include "Timing.h"
#include "ParticlesHelper.h"

#include<cmath>
#include <iostream>
#include <map>

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
map<string, float> progresses = {};
float lastPrintedSeconds = 0.f;
float maxTimeBetweenPrints = 0.8f;

void UniverseImpl::run() {
	cout << "Simulation running" << endl;
	cout << particles.size() << " particles" << endl;
	cout << "Frames: " << endTime << endl;
	timingTotal.setTime();
	output->output(particles, 0);
	this->progress = -1;
	int lawsRan = 0;
	bool particleDeleted = false;
	timingSections.setTime();
	if(USE_GPU == TRUE) {
		gpuDataController->putParticlesOnDevice(particles, true);
		updateSectionsTiming("Data to GPU");
	}
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		if(USE_GPU == TRUE) {
			if(particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
				updateSectionsTiming("Data to GPU");
			}
		}
		particleDeleted = false;
		for (const auto& l : laws) {
			if(USE_GPU == TRUE) {
				l->gpuRun(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuRun(particles);
			}
			updateSectionsTiming(l->getClassName());
			printPercentComplete(++lawsRan);
			updateSectionsTiming("Printing");
		}
		if(USE_GPU == TRUE) {
			gpuDataController->getParticlesFromDevice(particles);
			updateSectionsTiming("Data from GPU");
			particleDeleted = ParticlesHelper::removeDeletedParticles(particles);
			updateSectionsTiming("Deletions");
		}
		output->output(particles, i + 1);
		updateSectionsTiming("Data to JSON");
	}
	printPercentComplete(lawsRan, true);
	printSectionsTiming();
	cout << endl << "Simulation complete" << endl;
}

void UniverseImpl::printPercentComplete(int lawsRan, bool force) {
	float accurary = 1000.f;
	float fractionPassed = (lawsRan/(float)laws.size()) / endTime;
	progress = (100 * fractionPassed * accurary) / accurary;
	float elapsedSeconds = timingTotal.getTimeSeconds();
	if(force || elapsedSeconds - lastPrintedSeconds > maxTimeBetweenPrints) {
		lastPrintedSeconds = elapsedSeconds;
		float remainingPercent = 100 - progress;
		float timeRemaining = remainingPercent * (elapsedSeconds / progress);
		cout << "\r" << 
			"passed: " << progress << "% " << Timing::getTimeWithUnit(elapsedSeconds) << ", "
			"remaining: " << remainingPercent << "% " << Timing::getTimeWithUnit(timeRemaining) <<
			"                       " << std::flush;
	}
}

void UniverseImpl::updateSectionsTiming(string name) {
	if(progresses.find(name) == progresses.end()) {
		progresses[name] = 0;
	}
	progresses[name] += timingSections.getTimeSeconds();
	timingSections.setTime();
}

void UniverseImpl::printSectionsTiming() {
	string sections = "";
	for (auto const& it : progresses) {
		sections += it.first + ": " + Timing::getTimeWithUnit(it.second) + ", ";
	}
	cout << endl << sections << endl;
}


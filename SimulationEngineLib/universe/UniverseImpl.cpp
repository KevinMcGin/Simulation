#include "universe/UniverseImpl.h"
#include "util/Timing.h"
#include "particle/helper/ParticlesHelper.h"

#include <cmath>
#include <iostream>
#include <map>

UniverseImpl::UniverseImpl(
	vector<Law*> laws, 
	shared_ptr<SimulationInput> input, 
	shared_ptr<SimulationOutput> output, 
	unsigned int deltaTime, 
	unsigned long endTime,
	Usage use_gpu
) : Universe(input->input(), laws, output, deltaTime, endTime, use_gpu) {
	if(this->use_gpu == TRUE) {
		gpuDataController = new GpuDataController();
	}
}

UniverseImpl::~UniverseImpl() = default;

void UniverseImpl::run() {
	cout << "Simulation running" << endl;
	cout << particles.size() << " particles" << endl;
	cout << "Frames: " << endTime << endl;
	universeTiming.timingTotal.setTime();
	output->output(particles, 0);
	universeTiming.progress = -1;
	int lawsRan = 0;
	bool particleDeleted = false;
	universeTiming.timingSections.setTime();
	if(use_gpu == TRUE) {
		gpuDataController->putParticlesOnDevice(particles, true);
		updateSectionsTiming("Data to GPU");
	}
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		if(use_gpu == TRUE) {
			if(particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
				updateSectionsTiming("Data to GPU");
			}
		}
		particleDeleted = false;
		for (const auto& l : laws) {
			if(use_gpu == TRUE) {
				l->gpuLaw->run(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuLaw->run(particles);
			}
			updateSectionsTiming(l->gpuLaw->getClassName());
			printPercentComplete(++lawsRan);
			updateSectionsTiming("Printing");
		}
		if(use_gpu == TRUE) {
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
	universeTiming.progress = (100 * fractionPassed * accurary) / accurary;
	float elapsedSeconds = universeTiming.timingTotal.getTimeSeconds();
	if(force || elapsedSeconds - universeTiming.lastPrintedSeconds > universeTiming.maxTimeBetweenPrints) {
		universeTiming.lastPrintedSeconds = elapsedSeconds;
		float remainingPercent = 100 - universeTiming.progress;
		float timeRemaining = remainingPercent * ((elapsedSeconds-universeTiming.lastEstimatedSeconds) / (universeTiming.progress-universeTiming.lastEstimatedProgress));
		cout << "\r" << 
			"passed: " << universeTiming.progress << "% " << Timing::getTimeWithUnit(elapsedSeconds) << ", "
			"remaining: " << remainingPercent << "% " << Timing::getTimeWithUnit(timeRemaining) <<
			"                       " << std::flush;
	}
	if(elapsedSeconds - universeTiming.lastEstimatedSeconds > universeTiming.maxTimeBetweenEstimates) {
		universeTiming.lastEstimatedSeconds = elapsedSeconds;
		universeTiming.lastEstimatedProgress = universeTiming.progress;
	}
}

void UniverseImpl::updateSectionsTiming(string name) {
	if(universeTiming.progresses.find(name) == universeTiming.progresses.end()) {
		universeTiming.progresses[name] = 0;
	}
	universeTiming.progresses[name] += universeTiming.timingSections.getTimeSeconds();
	universeTiming.timingSections.setTime();
}

void UniverseImpl::printSectionsTiming() {
	string sections = "";
	for (auto const& it : universeTiming.progresses) {
		sections += it.first + ": " + Timing::getTimeWithUnit(it.second) + ", ";
	}
	cout << endl << sections << endl;
}


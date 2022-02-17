#include "universe/UniverseImpl.h"
#include "util/Timing.h"
#include "particle/helper/ParticlesHelper.h"

#include <cmath>
#include <iostream>
#include <map>

UniverseImpl::UniverseImpl(
	std::vector<Law*> laws, 
	std::shared_ptr<SimulationInput> input, 
	std::shared_ptr<SimulationOutput> output, 
	unsigned int deltaTime, 
	unsigned long endTime,
	Usage useGpu
) : Universe(input->input(), laws, output, deltaTime, endTime, useGpu) {
	if(this->useGpu == TRUE) {
		gpuDataController = new GpuDataController();
	}
}

UniverseImpl::~UniverseImpl() = default;

void UniverseImpl::run() {
	std::cout << "Simulation running" << std::endl;
	std::cout << particles.size() << " particles" << std::endl;
	std::cout << "Frames: " << endTime << std::endl;
	universeTiming.timingTotal.setTime();
	output->output(particles, 0);
	universeTiming.progress = -1;
	int lawsRan = 0;
	bool particleDeleted = false;
	universeTiming.timingSections.setTime();
	if(useGpu == TRUE) {
		gpuDataController->putParticlesOnDevice(particles, true);
		updateSectionsTiming("Data to GPU");
	}
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		if(useGpu == TRUE) {
			if(particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
				updateSectionsTiming("Data to GPU");
			}
		}
		particleDeleted = false;
		for (const auto& l : laws) {
			if(useGpu == TRUE) {
				l->gpuLaw->run(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuLaw->run(particles);
			}
			updateSectionsTiming(l->gpuLaw->getClassName());
			printPercentComplete(++lawsRan);
			updateSectionsTiming("Printing");
		}
		if(useGpu == TRUE) {
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
	std::cout << std::endl << "Simulation complete" << std::endl;
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
		std::cout << "\r" << 
			"passed: " << universeTiming.progress << "% " << Timing::getTimeWithUnit(elapsedSeconds) << ", "
			"remaining: " << remainingPercent << "% " << Timing::getTimeWithUnit(timeRemaining) <<
			"                       " << std::flush;
	}
	if(elapsedSeconds - universeTiming.lastEstimatedSeconds > universeTiming.maxTimeBetweenEstimates) {
		universeTiming.lastEstimatedSeconds = elapsedSeconds;
		universeTiming.lastEstimatedProgress = universeTiming.progress;
	}
}

void UniverseImpl::updateSectionsTiming(std::string name) {
	if(universeTiming.progresses.find(name) == universeTiming.progresses.end()) {
		universeTiming.progresses[name] = 0;
	}
	universeTiming.progresses[name] += universeTiming.timingSections.getTimeSeconds();
	universeTiming.timingSections.setTime();
}

void UniverseImpl::printSectionsTiming() {
	std::string sections = "";
	for (auto const& it : universeTiming.progresses) {
		sections += it.first + ": " + Timing::getTimeWithUnit(it.second) + ", ";
	}
	std::cout << std::endl << sections << std::endl;
}


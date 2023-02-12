#include "universe/UniverseImpl.h"
#include "util/Timing.h"
#include "particle/helper/ParticlesHelper.h"

#include <cmath>
#include <iostream>
#include <map>

UniverseImpl::UniverseImpl(
	std::vector<std::shared_ptr<Law>> laws, 
	std::shared_ptr<SimulationInput> input, 
	std::shared_ptr<SimulationOutput> output, 
	unsigned int deltaTime, 
	unsigned long endTime,
	Usage useGpu
) : Universe(input->input(), laws, output, deltaTime, endTime, useGpu) {
	if (this->useGpu == TRUE) {
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
	if (useGpu == TRUE) {
		gpuDataController->putParticlesOnDevice(particles, true);
		updateSectionsTiming("Data to GPU");
	}
	printPercentComplete(0, true);
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		printPercentComplete(i, false);
		if (useGpu == TRUE) {
			if (particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
				updateSectionsTiming("Data to GPU");
			}
		}
		particleDeleted = false;
		for (const auto& l : laws) {
			if (useGpu == TRUE) {
				l->gpuLaw->run(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuLaw->run(particles);
			}
			updateSectionsTiming(l->gpuLaw->getClassName());
			updateSectionsTiming("Printing");
			lawsRan++;
		}
		if (useGpu == TRUE) {
			gpuDataController->getParticlesFromDevice(particles);
			updateSectionsTiming("Data from GPU");
			particleDeleted = ParticlesHelper::removeDeletedParticles(particles);
			updateSectionsTiming("Deletions");
		}
		output->output(particles, i + 1);
		updateSectionsTiming("Data to JSON");
	}
	printPercentComplete(endTime, true);
	printSectionsTiming();
	std::cout << std::endl << "Simulation complete" << std::endl;
}

float round(float value, float accurary) {
	return std::round(value * accurary) / accurary;
}

void UniverseImpl::printPercentComplete(unsigned long time, bool force) {
	float fractionPassed = ((double)time) / endTime;
	universeTiming.progress = round(100 * fractionPassed, universeTiming.accurary);
	float elapsedSeconds = universeTiming.timingTotal.getTimeSeconds();
	if (force || elapsedSeconds - universeTiming.lastPrintedSeconds > universeTiming.maxTimeBetweenPrints) {
		universeTiming.lastPrintedSeconds = elapsedSeconds;
		float remainingPercent = 100 - universeTiming.progress;
		float timeRemaining = remainingPercent * ((elapsedSeconds-universeTiming.lastEstimatedSeconds) / (universeTiming.progress-universeTiming.lastEstimatedProgress));
		std::cout << "\r" << 
			"passed: " << universeTiming.progress << "% " << Timing::getTimeWithUnit(round(elapsedSeconds, universeTiming.accurary)) << ", "
			"remaining: " << remainingPercent << "% " << Timing::getTimeWithUnit(round(timeRemaining, universeTiming.accurary)) <<
			"                       " << std::flush;
	}
	if (elapsedSeconds - universeTiming.lastEstimatedSeconds >= universeTiming.minTimeBetweenEstimates) {
		universeTiming.lastEstimatedSeconds = elapsedSeconds;
		universeTiming.lastEstimatedProgress = universeTiming.progress;
	}
}


void UniverseImpl::updateSectionsTiming(std::string name) {
	if (universeTiming.progresses.find(name) == universeTiming.progresses.end()) {
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


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
) : Universe(input->input(), laws, output, deltaTime, endTime, useGpu),
	universeTiming(UniverseTiming(endTime)) {
	;
	if (this->useGpu == TRUE) {
		gpuDataController = new GpuDataController();
	}
}

UniverseImpl::~UniverseImpl() = default;

void UniverseImpl::run() {
	std::cout << "Simulation running" << std::endl;
	std::cout << particles.size() << " particles" << std::endl;
	std::cout << "Frames: " << endTime << std::endl;
	int lawsRan = 0;
	bool particleDeleted = false;
	output->output(particles, 0);
	universeTiming.start();
	universeTiming.printPercentComplete(0, true);
	if (useGpu == TRUE) {
		gpuDataController->putParticlesOnDevice(particles, true);
		universeTiming.updateSectionsTiming("Data to GPU");
	}
	for (unsigned long i = 0; i < endTime; i += deltaTime) {
		universeTiming.printPercentComplete(i, false);
		if (useGpu == TRUE) {
			if (particleDeleted) {
				gpuDataController->putParticlesOnDevice(particles);
				universeTiming.updateSectionsTiming("Data to GPU");
			}
		}
		particleDeleted = false;
		for (const auto& l : laws) {
			if (useGpu == TRUE) {
				l->gpuLaw->run(gpuDataController->get_td_par(), gpuDataController->getParticleCount());
			} else {
				l->cpuLaw->run(particles);
			}
			universeTiming.updateSectionsTiming(l->gpuLaw->getClassName());
			universeTiming.updateSectionsTiming("Printing");
			lawsRan++;
		}
		if (useGpu == TRUE) {
			gpuDataController->getParticlesFromDevice(particles);
			universeTiming.updateSectionsTiming("Data from GPU");
			particleDeleted = ParticlesHelper::removeDeletedParticles(particles);
			universeTiming.updateSectionsTiming("Deletions");
		}
		output->output(particles, i + 1);
		universeTiming.updateSectionsTiming("Data to JSON");
	}
	universeTiming.printPercentComplete(endTime, true);
	universeTiming.printSectionsTiming();
	std::cout << std::endl << "Simulation complete" << std::endl;
}

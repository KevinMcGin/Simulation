#include "cpp/universe/Universe.h"
#include <cstring>

const char* SIMULATION_USE_GPU = "SIMULATION_USE_GPU";

Universe::Universe(
    std::vector<Particle*> particles, 
    std::vector<std::shared_ptr<Law>> laws, 
    const std::shared_ptr<SimulationOutput> output, 
    float deltaTime,
    unsigned long endTime,
    Usage useGpu
) : particles(particles),
	laws(laws),
	output(output),
	deltaTime(deltaTime),
	endTime(endTime) {
	if (useGpu == UNDEFINED) {
        const char* envVar = std::getenv(SIMULATION_USE_GPU);
		envVar = envVar ? envVar : "true";
        if (strcmp(envVar, "true") == 0) {
            this->useGpu = TRUE;
        } else {
            this->useGpu = FALSE;
        }
    } else {
        this->useGpu = useGpu;
    }
    printUseGpu();
}

// The particles are this universe's to free: they are handed over as raw
// pointers by the input, and laws delete the ones they merge away mid-run
// (see ParticlesHelper::removeDeletedParticles), so whatever survives to
// the end has nobody else left to clean it up.
Universe::~Universe() {
	for (auto particle : particles) {
		delete particle;
	}
	particles.clear();
}

void Universe::printUseGpu() {
    if (this->useGpu == TRUE) {
        std::cout << "\nRunning on GPU\n";
    } else if (this->useGpu == FALSE) {
        std::cout << "\nRunning on CPU\n";
    } else {
        std::cout << "\nRunning on UNDEFINED\n";
    }
    
}

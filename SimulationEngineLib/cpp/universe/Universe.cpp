#include "cpp/universe/Universe.h"
#include <cstring>

const char* SIMULATION_USE_GPU = "SIMULATION_USE_GPU";

Universe::Universe(
    std::vector<Particle*> particles, 
    std::vector<std::shared_ptr<Law>> laws, 
    const std::shared_ptr<SimulationOutput> output, 
    unsigned int deltaTime,
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

Universe::~Universe() = default;

void Universe::printUseGpu() {
    if (this->useGpu == TRUE) {
        std::cout << "\nRunning on GPU\n";
    } else if (this->useGpu == FALSE) {
        std::cout << "\nRunning on CPU\n";
    } else {
        std::cout << "\nRunning on UNDEFINED\n";
    }
    
}

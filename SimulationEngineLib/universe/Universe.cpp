#include "universe/Universe.h"
#include <cstring>

const char* SIMULATION_USE_GPU = "SIMULATION_USE_GPU";

Universe::Universe(
    vector<Particle*> particles, 
    vector<Law*> laws, 
    const shared_ptr<SimulationOutput> output, 
    unsigned int deltaTime,
    unsigned long endTime,
    Usage useGpu
) : particles(particles),
	laws(laws),
	output(output),
	deltaTime(deltaTime),
	endTime(endTime) {
	if(useGpu == UNDEFINED) {
        const char* envVar = std::getenv(SIMULATION_USE_GPU);
		envVar = envVar ? envVar : "true";
        if(strcmp(envVar, "true") == 0) {
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
    if(this->useGpu == TRUE) {
        std::cout << std::endl << "Running on GPU" << std::endl;
    } else if(this->useGpu == FALSE) {
        std::cout << std::endl << "Running on CPU" << std::endl;
    } else {
        std::cout << std::endl << "Running on UNDEFINED" << std::endl;
    }
    
}

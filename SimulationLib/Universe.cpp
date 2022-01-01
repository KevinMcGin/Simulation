#include "Universe.h"
#include <cstring>

const char* SIMULATION_USE_GPU = "SIMULATION_USE_GPU";

Universe::Universe(
    vector<Particle*> particles, 
    vector<Law*> laws, 
    const shared_ptr<SimulationOutput> output, 
    unsigned int deltaTime,
    unsigned long endTime,
    Usage use_gpu
) : particles(particles),
	laws(laws),
	output(output),
	deltaTime(deltaTime),
	endTime(endTime) {
	if(use_gpu == UNDEFINED) {
        const char* envVar = std::getenv(SIMULATION_USE_GPU);
		envVar = envVar ? envVar : "true";
        if(strcmp(envVar, "true") == 0) {
            this->use_gpu = TRUE;
            std::cout << std::endl << "Running on GPU" << std::endl;
        }
        else {
            std::cout << std::endl << "Running on CPU" << std::endl;
            this->use_gpu = FALSE;
        }
    } else {
        this->use_gpu = use_gpu;
    }
}

Universe::~Universe() = default;

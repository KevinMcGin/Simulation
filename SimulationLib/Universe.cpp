#include "Universe.h"
#include <cstring>

const char* SIMULATION_USE_GPU = "SIMULATION_USE_GPU";
Usage Universe::USE_GPU = UNDEFINED;

Universe::Universe(vector<Particle*> particles, vector<Law*> laws, const shared_ptr<SimulationOutput> output, unsigned int deltaTime, unsigned long endTime)
    : particles(particles),
	laws(laws),
	output(output),
	deltaTime(deltaTime),
	endTime(endTime) {
	if(Universe::USE_GPU == UNDEFINED) {
        const char* envVar = std::getenv(SIMULATION_USE_GPU);
		if(!envVar) envVar = "true";
        if(strcmp(envVar, "true") == 0) {
            Universe::USE_GPU = TRUE;
            std::cout << std::endl << "Running on GPU" << std::endl;
        }
        else {
            std::cout << std::endl << "Running on CPU" << std::endl;
            Universe::USE_GPU = FALSE;
        }
    }
}

Universe::~Universe() = default;

#pragma once
#include "SimulationOutput.h"

#include <vector>
#include <iostream>

class SimulationOutputPrint: public SimulationOutput {
	public:
		virtual void output(vector<Particle*> particles, unsigned long time) {
			unsigned int i = 0;
			for (const auto& p : particles) {
				std::cout << "particle[" << i++ << "] position: "<< std::endl;
				std::cout << p->position[0] << std::endl;
				std::cout << p->position[1] << std::endl;
				std::cout << p->position[2] << std::endl;
			}
		};
};
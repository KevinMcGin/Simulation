#pragma once
#include "SimulationOutput.h"

#include <list>
#include <iostream>

class SimulationOutputSimple: public SimulationOutput {
	public:
		virtual void output(list<Particle*> particles) { 
			unsigned int i = 0;
			for (const auto& p : particles) {
				std::cout << "particle[" << i++ << "] position: "<< std::endl;
				std::cout << p->position[0] << std::endl;
				std::cout << p->position[1] << std::endl;
				std::cout << p->position[2] << std::endl;
			}
		};
};
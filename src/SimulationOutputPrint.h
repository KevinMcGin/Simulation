﻿#pragma once
#include "SimulationOutput.h"

#include <vector>
#include <iostream>

class SimulationOutputPrint: public SimulationOutput {
	public:
		virtual void output(vector<Particle*> particles, unsigned long time) {
			unsigned int i = 0;
			for (const auto& p : particles) {
				std::cout << "particle[" << i++ << "] position: "<< std::endl;
				std::cout << p->position.x << std::endl;
				std::cout << p->position.y << std::endl;
				std::cout << p->position.z << std::endl;
			}
		};
};
#pragma once
#include "Particle.cuh"

#include <vector>

class Law {
	public:
		virtual void run(vector<Particle*>& particles) = 0;
};
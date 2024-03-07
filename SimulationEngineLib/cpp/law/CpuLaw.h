#pragma once
#include "shared/particle/Particle.cuh"

#include <vector>

class CpuLaw {
public:
	virtual void run(std::vector<Particle*>& particles) = 0;
};
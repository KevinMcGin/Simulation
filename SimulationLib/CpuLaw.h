#pragma once
#include "Particle.cuh"

#include <vector>

class CpuLaw {
public:
	virtual void run(vector<Particle*>& particles) = 0;
};
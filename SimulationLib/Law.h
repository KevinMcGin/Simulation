#pragma once
#include "Particle.cuh"
#include "CpuLaw.h"
#include "GpuLaw.h"

#include <vector>

class Law {
public:
	Law(CpuLaw* cpuLaw, GpuLaw* gpuLaw);
	CpuLaw* cpuLaw;
	GpuLaw* gpuLaw;
};
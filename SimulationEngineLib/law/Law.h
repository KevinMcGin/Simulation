#pragma once
#include "particle/Particle.cuh"
#include "law/CpuLaw.h"
#include "law/GpuLaw.h"

#include <vector>

class Law {
public:
	Law(CpuLaw* cpuLaw, GpuLaw* gpuLaw);
	CpuLaw* cpuLaw;
	GpuLaw* gpuLaw;
};
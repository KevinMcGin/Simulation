#pragma once
#include "particle/Particle.cuh"
#include "law/CpuLaw.h"
#include "law/GpuLaw.h"

#include <vector>

class Law {
public:
	Law(std::shared_ptr<CpuLaw> cpuLaw, std::shared_ptr<GpuLaw> gpuLaw);
	std::shared_ptr<CpuLaw> cpuLaw;
	std::shared_ptr<GpuLaw> gpuLaw;
};
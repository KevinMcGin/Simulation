#pragma once
#include "shared/particle/Particle.cuh"
#include "cpp/law/CpuLaw.h"
#include "cpp/law/GpuLaw.h"

#include <vector>

class Law {
public:
	Law(
		std::string className,
		std::unique_ptr<CpuLaw> cpuLaw, 
		std::unique_ptr<GpuLaw> gpuLaw
	);
	std::unique_ptr<CpuLaw> cpuLaw;
	std::unique_ptr<GpuLaw> gpuLaw;

	std::string getClassName() { return className; }
private:
	std::string className = "Law";
};
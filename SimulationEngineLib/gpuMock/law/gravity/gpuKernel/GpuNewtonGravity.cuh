#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/law/GpuLaw.h"
#include "shared/service/momentum/MomentumService.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuNewtonGravity: public GpuLaw {
public:
	GpuNewtonGravity(
		Real G,
		std::shared_ptr<MomentumService> momentumService
	);
	void run(
		Particle** particles, 
		int particleCount,
		Real deltaTime
	) override;
};
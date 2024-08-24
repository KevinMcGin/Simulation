#pragma once
#include "cpp/law/GpuLaw.h"
#include "shared/service/momentum/MomentumService.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuNewtonGravity: public GpuLaw {
public:
	GpuNewtonGravity(
		float G,
		std::shared_ptr<MomentumService> momentumService
	);
	void run(
		Particle** particles, 
		int particleCount,
		unsigned int deltaTime
	) override;
};
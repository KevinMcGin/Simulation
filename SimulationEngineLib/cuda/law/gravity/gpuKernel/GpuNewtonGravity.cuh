#pragma once
#include "cpp/law/GpuLaw.h"

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
protected:
	const float G;
	std::shared_ptr<MomentumService> momentumService;

private:
    MomentumService** momentumServiceGpu = NULL;
};
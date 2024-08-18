#pragma once
#include "cpp/law/CpuLaw.h"
#include "shared/service/momentum/MomentumService.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonGravity: public CpuLaw {
public:
	CpuNewtonGravity(
		float G,
		std::shared_ptr<MomentumService> momentumService
	);
	void run(
		std::vector<Particle*>& particles,
		unsigned int deltaTime
	) override;
protected:
	const float G;
	std::shared_ptr<MomentumService> momentumService;
};
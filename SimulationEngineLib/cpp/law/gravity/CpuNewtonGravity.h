#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/law/CpuLaw.h"
#include "shared/service/momentum/MomentumService.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>
#include <memory>

class CpuNewtonGravity: public CpuLaw {
public:
	CpuNewtonGravity(
		Real G,
		std::shared_ptr<MomentumService> momentumService
	);
	void run(
		std::vector<Particle*>& particles,
		Real deltaTime
	) override;
protected:
	const Real G;
	std::shared_ptr<MomentumService> momentumService;
};
#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/law/GpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuNewtonFirstLaw: public GpuLaw {
public:
	GpuNewtonFirstLaw();
	void run(
		Particle** particles, 
		int particleCount,
		Real deltaTime
	) override;
};
#pragma once
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
		unsigned int deltaTime
	) override;
};
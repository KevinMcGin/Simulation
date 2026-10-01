#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/law/CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonFirstLaw: public CpuLaw {
public:
	CpuNewtonFirstLaw();
	virtual void run(
		std::vector<Particle*>& particles,
		Real deltaTime
	);
};
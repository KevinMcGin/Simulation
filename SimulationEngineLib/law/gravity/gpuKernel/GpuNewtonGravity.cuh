#pragma once
#include "law/GpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuNewtonGravity: public GpuLaw {
public:
	GpuNewtonGravity(float G);
	void run(Particle** particles, int particleCount) override;
protected:
	const float G;
};
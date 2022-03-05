#pragma once
#include "law/GpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuNewtonGravity: public GpuLaw {
public:
	GpuNewtonGravity(float G);
	virtual void run(Particle** particles, int particleCount);
protected:
	const float G;
};
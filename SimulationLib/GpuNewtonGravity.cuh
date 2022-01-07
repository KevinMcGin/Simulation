#pragma once
#include "GpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class GpuNewtonGravity: public GpuLaw {
public:
	GpuNewtonGravity(double G);
	virtual void run(Particle** td_par, int particleCount);
protected:
	const double G;
};
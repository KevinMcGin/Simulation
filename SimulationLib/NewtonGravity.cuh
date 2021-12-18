#pragma once
#include "Law.h"
#include "PhysicalConstants.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonGravity: public Law {
public:
	NewtonGravity();
	NewtonGravity(double G);

	virtual void cpuRun(vector<Particle*>& particles);
	virtual void gpuRun(Particle** td_par, int particleCount);

protected:
	const double G;
};
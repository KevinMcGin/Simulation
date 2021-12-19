#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonFirstLaw: public Law {
public:
	NewtonFirstLaw();
	virtual void cpuRun(vector<Particle*>& particles);
	virtual void gpuRun(Particle** td_par, int particleCount);
};
#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonFirstLaw: public Law {
public:
	virtual void cpuRun(vector<Particle*>& particles);
	virtual void gpuRun(vector<Particle*>& particles);
		
};
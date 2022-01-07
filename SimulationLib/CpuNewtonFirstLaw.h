#pragma once
#include "CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonFirstLaw: public CpuLaw {
public:
	CpuNewtonFirstLaw();
	virtual void run(vector<Particle*>& particles);
};
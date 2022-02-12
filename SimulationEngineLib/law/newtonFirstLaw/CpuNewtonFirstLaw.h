#pragma once
#include "law/CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonFirstLaw: public CpuLaw {
public:
	CpuNewtonFirstLaw();
	virtual void run(std::vector<Particle*>& particles);
};
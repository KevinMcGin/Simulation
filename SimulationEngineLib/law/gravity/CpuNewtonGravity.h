#pragma once
#include "law/CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonGravity: public CpuLaw {
public:
	CpuNewtonGravity(double G);
	virtual void run(std::vector<Particle*>& particles);
protected:
	const double G;
};
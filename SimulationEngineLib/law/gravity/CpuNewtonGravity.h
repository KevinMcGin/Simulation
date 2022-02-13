#pragma once
#include "law/CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonGravity: public CpuLaw {
public:
	CpuNewtonGravity(float G);
	virtual void run(std::vector<Particle*>& particles);
protected:
	const float G;
};
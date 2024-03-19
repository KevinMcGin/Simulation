#pragma once
#include "cpp/law/CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonGravity: public CpuLaw {
public:
	CpuNewtonGravity(float G);
	void run(
		std::vector<Particle*>& particles,
		unsigned int deltaTime
	) override;
protected:
	const float G;
};
﻿#pragma once
#include "law/CpuLaw.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class CpuNewtonGravity: public CpuLaw {
public:
	CpuNewtonGravity(float G);
	void run(std::vector<Particle*>& particles) override;
protected:
	const float G;
};
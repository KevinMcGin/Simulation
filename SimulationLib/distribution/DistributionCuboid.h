﻿#pragma once
#include "distribution/Distribution3D.h"

using namespace std;

class DistributionCuboid : public Distribution3D {
public:
	DistributionCuboid(Vector3D mean, Vector3D delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	virtual  Vector3D getValue();

private:
	const Vector3D mean, delta;

};
#pragma once
#include "distribution/DistributionSphere.h"



class DistributionCircle: public DistributionSphere {
public:
	DistributionCircle(Vector3D mean, double delta);

	virtual  Vector3D getValue();
};
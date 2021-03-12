#pragma once
#include "DistributionSphere.h"

using namespace std;

class DistributionCircle: public DistributionSphere {
public:
	DistributionCircle(Vector3D mean, double delta);

	virtual  Vector3D getValue();
};
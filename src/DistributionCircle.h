#pragma once
#include "DistributionGlobe.h"

using namespace std;

class DistributionCircle: public DistributionGlobe {
public:
	DistributionCircle(Vector3D mean, double delta);

	virtual  Vector3D getValue();
};
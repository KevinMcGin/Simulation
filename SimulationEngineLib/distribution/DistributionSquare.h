#pragma once
#include "distribution/DistributionCuboid.h"

using namespace std;

class DistributionSquare: public DistributionCuboid {
public:
	DistributionSquare(Vector3D mean, double delta);

};
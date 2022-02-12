#pragma once
#include "distribution/DistributionCuboid.h"



class DistributionSquare: public DistributionCuboid {
public:
	DistributionSquare(Vector3D mean, double delta);

};
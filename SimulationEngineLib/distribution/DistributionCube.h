#pragma once
#include "distribution/DistributionCuboid.h"



class DistributionCube : public DistributionCuboid {
public:
	DistributionCube(Vector3D mean, double delta);;
};
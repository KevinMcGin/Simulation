#pragma once
#include "distribution/DistributionCuboid.h"



class DistributionSquare: public DistributionCuboid {
public:
	DistributionSquare(Vector3D<float> mean, float delta);

};
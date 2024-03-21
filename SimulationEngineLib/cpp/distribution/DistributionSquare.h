#pragma once
#include "cpp/distribution/DistributionCuboid.h"



class DistributionSquare: public DistributionCuboid {
public:
	DistributionSquare(Vector3D<float> mean, float delta);

};
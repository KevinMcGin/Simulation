#pragma once
#include "cpp/distribution/DistributionCuboid.h"



class DistributionCube : public DistributionCuboid {
public:
	DistributionCube(Vector3D<float> mean, float delta);;
};
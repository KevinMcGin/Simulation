#pragma once
#include "cpp/distribution/DistributionSphere.h"



class DistributionCircle: public DistributionSphere {
public:
	DistributionCircle(Vector3D<float> mean, float delta);

	Vector3D<float> getValue() override;
};
#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/DistributionSphere.h"

class DistributionCircle: public DistributionSphere {
public:
	DistributionCircle(Vector3D<Real> mean, Real delta);

	Vector3D<Real> getValue() override;
};
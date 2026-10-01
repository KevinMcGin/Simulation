#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/DistributionCuboid.h"



class DistributionCube : public DistributionCuboid {
public:
	DistributionCube(Vector3D<Real> mean, Real delta);;
};
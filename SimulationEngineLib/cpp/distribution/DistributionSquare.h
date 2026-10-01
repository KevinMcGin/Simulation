#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/DistributionCuboid.h"



class DistributionSquare: public DistributionCuboid {
public:
	DistributionSquare(Vector3D<Real> mean, Real delta);

};
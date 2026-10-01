#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 

class DistributionSphere : public Distribution3D {
public:
	DistributionSphere(Vector3D<Real> mean, Real delta);

	Vector3D<Real> getValue() override;

protected:
	const Vector3D<Real> mean;
	const Real delta;
};
#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 

class DistributionGlobe: public Distribution3D {
public:
	DistributionGlobe(Vector3D<Real> mean, Vector3D<Real> delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	Vector3D<Real> getValue() override;

private:
	const Vector3D<Real> mean, delta;

};
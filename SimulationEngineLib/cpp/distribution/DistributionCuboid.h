#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/Distribution3D.h"



class DistributionCuboid : public Distribution3D {
public:
	DistributionCuboid(Vector3D<Real> mean, Vector3D<Real> delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	Vector3D<Real> getValue() override;

private:
	const Vector3D<Real> mean, delta;

};
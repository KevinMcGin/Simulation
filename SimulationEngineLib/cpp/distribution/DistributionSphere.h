#pragma once
#include "cpp/distribution/Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 



class DistributionSphere : public Distribution3D {
public:
	DistributionSphere(Vector3D<float> mean, float delta);

	Vector3D<float> getValue() override;

protected:
	const Vector3D<float> mean;
	const float delta;
};
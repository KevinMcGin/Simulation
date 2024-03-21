#pragma once
#include "cpp/distribution/Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 



class DistributionGlobe: public Distribution3D {
public:
	DistributionGlobe(Vector3D<float> mean, Vector3D<float> delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	Vector3D<float> getValue() override;

private:
	const Vector3D<float> mean, delta;

};
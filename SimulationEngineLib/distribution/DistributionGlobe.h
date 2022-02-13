#pragma once
#include "distribution/Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 



class DistributionGlobe: public Distribution3D {
public:
	DistributionGlobe(Vector3D<float> mean, Vector3D<float> delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	virtual  Vector3D<float> getValue();

private:
	const Vector3D<float> mean, delta;

};
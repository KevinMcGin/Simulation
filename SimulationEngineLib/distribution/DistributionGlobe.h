#pragma once
#include "distribution/Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 

using namespace std;

class DistributionGlobe: public Distribution3D {
public:
	DistributionGlobe(Vector3D mean, Vector3D delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	virtual  Vector3D getValue();

private:
	const Vector3D mean, delta;

};
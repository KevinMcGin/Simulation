#pragma once
#include "Distribution3D.h"

using namespace std;

class DistributionGlobe: public Distribution3D {
public:
	DistributionGlobe(Vector3D mean, Vector3D delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	virtual  Vector3D getValue() {
		return { random(mean.x, delta.x), random(mean.y, delta.y), random(mean.z, delta.z) };
	};

private:
	const Vector3D mean, delta;

};
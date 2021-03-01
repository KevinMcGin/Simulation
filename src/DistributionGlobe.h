#pragma once
#include "Distribution3D.h"

using namespace std;

class DistributionGlobe: public Distribution3D {
public:
	DistributionGlobe(array<double, 3> mean, array<double, 3> delta): Distribution3D(),
		mean(mean),
		delta(delta)
	{};

	virtual  array<double, 3> getValue() {
		return { random(mean[0], delta[0]), random(mean[1], delta[1]), random(mean[2], delta[2]) };
	};

private:
	const array<double, 3> mean, delta;

};
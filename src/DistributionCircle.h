#pragma once
#include "Distribution3D.h"

using namespace std;

class DistributionCircle: public Distribution3D {
public:
	DistributionCircle(array<double, 3> mean, double delta): Distribution3D(),
		mean(mean),
		delta(delta)
		{};

	virtual  array<double, 3> getValue() {
		return { random(mean[0], delta), random(mean[1], delta), random(mean[2], 0) };
	};

private:
	const array<double, 3> mean;
	const double delta;
};
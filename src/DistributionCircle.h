#pragma once
#include "DistributionGlobe.h"

using namespace std;

class DistributionCircle: public DistributionGlobe {
public:
	DistributionCircle(array<double, 3> mean, double delta) : DistributionGlobe(mean, { delta, delta, 0 }) {};

};
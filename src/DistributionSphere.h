#pragma once
#include "DistributionGlobe.h"

using namespace std;

class DistributionSphere : public DistributionGlobe {
public:
	DistributionSphere(array<double, 3> mean, double delta) : DistributionGlobe(mean, { delta, delta, delta }) {};
};
#pragma once
#include "DistributionGlobe.h"

using namespace std;

class DistributionSphere : public DistributionGlobe {
public:
	DistributionSphere(Vector3D mean, double delta) : DistributionGlobe(mean, { delta, delta, delta }) {};
};
#pragma once
#include "Distribution3D.h"
#define _USE_MATH_DEFINES
#include <cmath> 

using namespace std;

class DistributionSphere : public Distribution3D {
public:
	DistributionSphere(Vector3D mean, double delta);

	virtual Vector3D getValue() override;

protected:
	const Vector3D mean;
	const double delta;
};
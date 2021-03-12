#pragma once
#include "DistributionCuboid.h"

using namespace std;

class DistributionCube : public DistributionCuboid {
public:
	DistributionCube(Vector3D mean, double delta);;
};
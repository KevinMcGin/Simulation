#pragma once
#include "shared/precision/Real.cuh"
#include <stdlib.h>   
#include <time.h>

class DistributionDensity
{
public:
	DistributionDensity() {};

	virtual void getMassRadius(Real &mass, Real &radius) = 0;
};


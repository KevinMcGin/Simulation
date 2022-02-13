#pragma once
#include <stdlib.h>   
#include <time.h>

class DistributionDensity
{
public:
	DistributionDensity() {};

	virtual void getMassRadius(float &mass, float &radius) = 0;
};


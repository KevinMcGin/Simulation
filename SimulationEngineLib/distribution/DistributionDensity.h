#pragma once
#include <stdlib.h>   
#include <time.h>

class DistributionDensity
{
public:
	DistributionDensity() {};

	virtual void getMassRadius(double &mass, double &radius) = 0;
};


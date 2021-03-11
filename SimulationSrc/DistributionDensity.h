#pragma once
#include <stdlib.h>   
#include <time.h>

class DistributionDensity
{
public:
	DistributionDensity() { srand(time(NULL)); };

	virtual void getMassRadius(double &mass, double &radius) = 0;
};


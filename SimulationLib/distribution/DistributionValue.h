#pragma once
#include "distribution/Distribution.h"
class DistributionValue : public Distribution
{
public:
	DistributionValue(double value);
	virtual double getValue();

private:
	const double value;
};


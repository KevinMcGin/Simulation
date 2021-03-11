#pragma once
#include "Distribution.h"
class DistributionValue : public Distribution
{
public:
	DistributionValue(double value);
	virtual double getValue();

private:
	const double value;
};


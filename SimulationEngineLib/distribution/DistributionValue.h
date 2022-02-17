#pragma once
#include "distribution/Distribution.h"
class DistributionValue : public Distribution
{
public:
	DistributionValue(float value);
	virtual float getValue();

private:
	const float value;
};


#pragma once
#include "cpp/distribution/Distribution.h"
class DistributionValue : public Distribution
{
public:
	DistributionValue(float value);
	float getValue() override;

private:
	const float value;
};


#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/Distribution.h"
class DistributionValue : public Distribution
{
public:
	DistributionValue(Real value);
	Real getValue() override;

private:
	const Real value;
};


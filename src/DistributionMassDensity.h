#pragma once
#include "DistributionDensity.h"
#include "Distribution.h"

class DistributionMassDensity :
    public DistributionDensity
{
public:
	DistributionMassDensity(Distribution* massDistribution, Distribution* densityDistribution);
	void getMassRadius(double& mass, double& radius) override;

private:
	Distribution* massDistribution;
	Distribution* densityDistribution;

};


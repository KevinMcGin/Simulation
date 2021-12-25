#pragma once
#define _USE_MATH_DEFINES
#include "DistributionDensity.h"
#include "Distribution.h"
#include <memory>

class DistributionMassDensity :
    public DistributionDensity
{
public:
	DistributionMassDensity(std::shared_ptr<Distribution> massDistribution, std::shared_ptr<Distribution> densityDistribution);
	void getMassRadius(double& mass, double& radius) override;

private:
	std::shared_ptr<Distribution> massDistribution;
	std::shared_ptr<Distribution> densityDistribution;

};


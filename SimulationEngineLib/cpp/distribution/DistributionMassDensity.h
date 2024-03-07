#pragma once
#define _USE_MATH_DEFINES
#include <memory>

#include "cpp/distribution/DistributionDensity.h"
#include "cpp/distribution/Distribution.h"

class DistributionMassDensity :
    public DistributionDensity
{
public:
	DistributionMassDensity(std::shared_ptr<Distribution> massDistribution, std::shared_ptr<Distribution> densityDistribution);
	void getMassRadius(float& mass, float& radius) override;

private:
	std::shared_ptr<Distribution> massDistribution;
	std::shared_ptr<Distribution> densityDistribution;

};


#include "DistributionMassDensity.h"
#define _USE_MATH_DEFINES
#include <cmath>

DistributionMassDensity::DistributionMassDensity(Distribution* massDistribution, Distribution* densityDistribution)
	:DistributionDensity(),
	massDistribution(massDistribution),
	densityDistribution(densityDistribution)
{

}

void DistributionMassDensity::getMassRadius(double& mass, double& radius)
{
	double density = densityDistribution->getValue();
	mass = massDistribution->getValue();
	radius = pow(3 * mass / (4 * M_PI * density), 1 / 3.0);

}

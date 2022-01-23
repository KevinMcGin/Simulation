#include "distribution/DistributionMassDensity.h"
#include <cmath>

DistributionMassDensity::DistributionMassDensity(std::shared_ptr<Distribution> massDistribution, std::shared_ptr<Distribution> densityDistribution)
	: DistributionDensity(),
	massDistribution(massDistribution),
	densityDistribution(densityDistribution) { }

void DistributionMassDensity::getMassRadius(double& mass, double& radius) {
	double density = densityDistribution->getValue();
	mass = massDistribution->getValue();
	radius = pow(3 * mass / (4 * M_PI * density), 1 / 3.0);

}

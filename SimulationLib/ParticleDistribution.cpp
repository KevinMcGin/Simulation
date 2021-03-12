#include "ParticleDistribution.h"



ParticleDistribution::ParticleDistribution(DistributionDensity* densityDistribution, Distribution3D* positionDistribution, Distribution3D* velocityDistribution, Distribution3D* angularVelocityDistribution) :
	densityDistribution(densityDistribution),
	positionDistribution(positionDistribution),
	velocityDistribution(velocityDistribution),
	angularVelocityDistribution(angularVelocityDistribution)
{

}

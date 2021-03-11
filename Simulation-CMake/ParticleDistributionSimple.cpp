#include "ParticleDistributionSimple.h"



ParticleDistributionSimple::ParticleDistributionSimple(DistributionDensity* densityDistribution, Distribution3D* positionDistribution, Distribution3D* velocitysDistribution, Distribution3D* angularVelocityDistribution) :
	ParticleDistribution(densityDistribution, positionDistribution, velocitysDistribution, angularVelocityDistribution)
{

}

Particle* ParticleDistributionSimple::getParticle()
{
	double mass, radius;
	densityDistribution->getMassRadius(mass, radius);

	return new ParticleSimple(mass, radius, positionDistribution->getValue(), velocityDistribution->getValue(), angularVelocityDistribution->getValue());
}

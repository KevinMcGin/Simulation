#include "ParticleDistributionSimple.h"



ParticleDistributionSimple::ParticleDistributionSimple(Distribution* massDistribution, Distribution* radiusDistribution, Distribution3D* positionDistrubtion, Distribution3D* velocityDistrubtion, Distribution3D* angularVelocityDistrubtion) :
	ParticleDistribution(massDistribution, radiusDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion)
{

}

Particle* ParticleDistributionSimple::getParticle()
{
	return new ParticleSimple(massDistribution->getValue(), radiusDistribution->getValue(), positionDistrubtion->getValue(), velocityDistrubtion->getValue(), angularVelocityDistrubtion->getValue());
}

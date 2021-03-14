#include "ParticleDistributionSimple.h"
#include "ParticleSimple.h"


ParticleDistributionSimple::ParticleDistributionSimple(DistributionDensity* densityDistribution, Distribution3D* positionDistribution, Distribution3D* velocityDistribution, Distribution3D* angularVelocityDistribution) :
	ParticleDistribution(),
	densityDistribution(densityDistribution),
	positionDistribution(positionDistribution),
	velocityDistribution(velocityDistribution),
	angularVelocityDistribution(angularVelocityDistribution)
{

}

Particle* ParticleDistributionSimple::getParticle()
{
	double mass, radius;
	densityDistribution->getMassRadius(mass, radius);
	Vector3D position = positionDistribution->getValue();
	Vector3D velocity = velocityDistribution->getValue();
	Vector3D angularVelocity = angularVelocityDistribution->getValue();

	return new ParticleSimple(
		mass, radius, 
		position, velocity, 
		angularVelocity
	);
}

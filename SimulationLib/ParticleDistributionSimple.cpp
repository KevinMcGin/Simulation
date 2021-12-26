#include <memory>

#include "ParticleDistributionSimple.h"
#include "ParticleSimple.h"

ParticleDistributionSimple::ParticleDistributionSimple(
		std::shared_ptr<DistributionDensity> densityDistribution,
		std::shared_ptr<Distribution3D> positionDistribution, 
		std::shared_ptr<Distribution3D> velocityDistribution, 
		std::shared_ptr<Distribution3D> angularVelocityDistribution
	) : ParticleDistribution(),
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

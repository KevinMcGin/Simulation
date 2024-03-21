#include <memory>

#include "cpp/distribution/ParticleDistributionSimple.h"
#include "cpp/particle/ParticleSimple.h"

ParticleDistributionSimple::ParticleDistributionSimple(
		std::shared_ptr<DistributionDensity> densityDistribution,
		std::shared_ptr<Distribution3D> positionDistribution, 
		std::shared_ptr<Distribution3D> velocityDistribution//, 
		// std::shared_ptr<Distribution3D> angularVelocityDistribution
	) : ParticleDistribution(),
	densityDistribution(densityDistribution),
	positionDistribution(positionDistribution),
	velocityDistribution(velocityDistribution)//,
	// angularVelocityDistribution(angularVelocityDistribution)
{

}

Particle* ParticleDistributionSimple::getParticle()
{
	float mass, radius;
	densityDistribution->getMassRadius(mass, radius);
	Vector3D<float> position = positionDistribution->getValue();
	Vector3D<float> velocity = velocityDistribution->getValue();
	// Vector3D<float> angularVelocity = angularVelocityDistribution->getValue();

	return new ParticleSimple(
		mass, 
		radius, 
		position,
		velocity//, 
		// angularVelocity
	);
}

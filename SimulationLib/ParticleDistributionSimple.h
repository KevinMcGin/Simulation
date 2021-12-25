#pragma once
#include "ParticleDistribution.h"

class ParticleDistributionSimple: public ParticleDistribution {
public:
	ParticleDistributionSimple(
		shared_ptr<DistributionDensity> densityDistribution,
		shared_ptr<Distribution3D> positionDistribution, 
		shared_ptr<Distribution3D> velocityDistribution, 
		shared_ptr<Distribution3D> angularVelocityDistribution
	);

	virtual Particle* getParticle();

private:
	shared_ptr<DistributionDensity> densityDistribution;
	shared_ptr<Distribution3D> positionDistribution;
	shared_ptr<Distribution3D> velocityDistribution;
	shared_ptr<Distribution3D> angularVelocityDistribution;
};
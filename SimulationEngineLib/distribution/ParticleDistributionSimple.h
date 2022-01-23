#pragma once
#include <memory>

#include "distribution/ParticleDistribution.h"

class ParticleDistributionSimple: public ParticleDistribution {
public:
	ParticleDistributionSimple(
		std::shared_ptr<DistributionDensity> densityDistribution,
		std::shared_ptr<Distribution3D> positionDistribution, 
		std::shared_ptr<Distribution3D> velocityDistribution, 
		std::shared_ptr<Distribution3D> angularVelocityDistribution
	);

	virtual Particle* getParticle();

private:
	std::shared_ptr<DistributionDensity> densityDistribution;
	std::shared_ptr<Distribution3D> positionDistribution;
	std::shared_ptr<Distribution3D> velocityDistribution;
	std::shared_ptr<Distribution3D> angularVelocityDistribution;
};
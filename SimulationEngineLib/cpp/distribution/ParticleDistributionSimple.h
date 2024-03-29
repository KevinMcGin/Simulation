﻿#pragma once
#include <memory>

#include "cpp/distribution/ParticleDistribution.h"

class ParticleDistributionSimple: public ParticleDistribution {
public:
	ParticleDistributionSimple(
		std::shared_ptr<DistributionDensity> densityDistribution,
		std::shared_ptr<Distribution3D> positionDistribution, 
		std::shared_ptr<Distribution3D> velocityDistribution//, 
		// std::shared_ptr<Distribution3D> angularVelocityDistribution
	);

	Particle* getParticle() override;

private:
	std::shared_ptr<DistributionDensity> densityDistribution;
	std::shared_ptr<Distribution3D> positionDistribution;
	std::shared_ptr<Distribution3D> velocityDistribution;
	// std::shared_ptr<Distribution3D> angularVelocityDistribution;
};
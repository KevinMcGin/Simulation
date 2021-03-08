#pragma once
#include "ParticleDistribution.h"
#include "ParticleSimple.h"

class ParticleDistributionSimple: public ParticleDistribution {
public:
	ParticleDistributionSimple(DistributionDensity* densityDistribution,
		Distribution3D* positionDistribution, Distribution3D* velocityDistribution, Distribution3D* angularVelocityDistribution);

	virtual Particle* getParticle();
};
#pragma once
#include "ParticleDistribution.h"
#include "ParticleSimple.h"

class ParticleDistributionSimple: public ParticleDistribution {
public:
	ParticleDistributionSimple(Distribution* massDistribution, Distribution* radiusDistribution, Distribution3D* positionDistrubtion, Distribution3D* velocityDistrubtion, Distribution3D* angularVelocityDistrubtion);

	virtual Particle* getParticle();
};
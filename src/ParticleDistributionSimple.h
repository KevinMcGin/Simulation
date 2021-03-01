#pragma once
#include "ParticleDistribution.h"
#include "ParticleSimple.h"

class ParticleDistributionSimple: public ParticleDistribution {
public:
	ParticleDistributionSimple(Distribution* massDistribution, Distribution* radiusDistribution, Distribution3D* positionDistrubtion, Distribution3D* velocityDistrubtion, Distribution3D* angularVelocityDistrubtion): 
		ParticleDistribution(massDistribution, radiusDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion)
	{};

	virtual Particle* getParticle() {
		return new ParticleSimple(massDistribution->getValue(), radiusDistribution->getValue(), positionDistrubtion->getValue(), velocityDistrubtion->getValue(), angularVelocityDistrubtion->getValue());
	};
};
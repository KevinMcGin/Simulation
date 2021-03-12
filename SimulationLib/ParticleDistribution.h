#pragma once
#include "Distribution.h"
#include "DistributionDensity.h"
#include "Distribution3D.h"
#include "Particle.h"

class ParticleDistribution {
public:
	ParticleDistribution(DistributionDensity* densityDistribution, Distribution3D* positionDistribution,
		Distribution3D* velocityDistribution, Distribution3D* angularVelocityDistribution);

	virtual Particle* getParticle() = 0;

protected:
	DistributionDensity* densityDistribution;
	Distribution3D* positionDistribution;
	Distribution3D* velocityDistribution;
	Distribution3D* angularVelocityDistribution;
};
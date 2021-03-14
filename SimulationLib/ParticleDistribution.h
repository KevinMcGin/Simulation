#pragma once
#include "Distribution.h"
#include "DistributionDensity.h"
#include "Distribution3D.h"
#include "Particle.h"

class ParticleDistribution {
public:
	ParticleDistribution();

	virtual Particle* getParticle() = 0;

};
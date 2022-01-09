#pragma once
#include "distribution/Distribution.h"
#include "distribution/DistributionDensity.h"
#include "distribution/Distribution3D.h"
#include "particle/Particle.cuh"

class ParticleDistribution {
public:
	ParticleDistribution();

	virtual Particle* getParticle() = 0;

};
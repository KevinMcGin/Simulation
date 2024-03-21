#pragma once
#include "cpp/distribution/Distribution.h"
#include "cpp/distribution/DistributionDensity.h"
#include "cpp/distribution/Distribution3D.h"
#include "shared/particle/Particle.cuh"

class ParticleDistribution {
public:
	ParticleDistribution();

	virtual Particle* getParticle() = 0;

};
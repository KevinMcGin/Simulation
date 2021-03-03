#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "ParticleDistributionSimple.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(unsigned long particleCount, ParticleDistributionSimple particleDistribution) :
		particleCount(particleCount),
		particleDistribution(particleDistribution) {}

	virtual vector<Particle*> input() {

		vector<Particle*> particles;
		for (unsigned long i = 0; i < particleCount; i++) {
			particles.push_back(particleDistribution.getParticle());
		}

		return particles;
	}



private:
	const unsigned long particleCount;
	ParticleDistributionSimple particleDistribution;
};
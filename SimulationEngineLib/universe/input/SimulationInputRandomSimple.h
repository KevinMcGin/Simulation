#pragma once
#include <memory>

#include "universe/input/SimulationInput.h"
#include "particle/ParticleSimple.h"
#include "distribution/DistributionSimple.h"
#include "distribution/DistributionCircle.h"
#include "distribution/ParticleDistribution.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(vector<unsigned long> particleCounts, vector<std::shared_ptr<ParticleDistribution>> particleDistributions);

	virtual vector<Particle*> input();


private:
	vector<unsigned long> particleCounts;
	vector<std::shared_ptr<ParticleDistribution>> particleDistributions;
};
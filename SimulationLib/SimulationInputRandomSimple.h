#pragma once
#include <memory>

#include "SimulationInput.h"
#include "ParticleSimple.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "ParticleDistribution.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(vector<unsigned long> particleCounts, vector<std::shared_ptr<ParticleDistribution>> particleDistributions);

	virtual vector<Particle*> input();


private:
	vector<unsigned long> particleCounts;
	vector<std::shared_ptr<ParticleDistribution>> particleDistributions;
};
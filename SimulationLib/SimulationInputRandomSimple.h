#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "ParticleDistribution.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(vector<unsigned long> particleCounts, vector<shared_ptr<ParticleDistribution>> particleDistributions);

	virtual vector<Particle*> input();


private:
	vector<unsigned long> particleCounts;
	vector<shared_ptr<ParticleDistribution>> particleDistributions;
};
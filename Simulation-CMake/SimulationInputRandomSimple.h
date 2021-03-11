#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "ParticleDistributionSimple.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(vector<unsigned long> particleCounts, vector < ParticleDistributionSimple> particleDistributions);

	virtual vector<Particle*> input();


private:
	vector<unsigned long> particleCounts;
	vector<ParticleDistributionSimple> particleDistributions;
};
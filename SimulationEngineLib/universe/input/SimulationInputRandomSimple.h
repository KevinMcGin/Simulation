#pragma once
#include <memory>

#include "universe/input/SimulationInput.h"
#include "particle/ParticleSimple.h"
#include "distribution/DistributionSimple.h"
#include "distribution/DistributionCircle.h"
#include "distribution/ParticleDistribution.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(std::vector<unsigned long> particleCounts, std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions);

	std::vector<Particle*> input() override;


private:
	std::vector<unsigned long> particleCounts;
	std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions;
};
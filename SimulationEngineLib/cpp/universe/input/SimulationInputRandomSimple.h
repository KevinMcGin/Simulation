#pragma once
#include <memory>

#include "cpp/universe/input/SimulationInput.h"
#include "cpp/particle/ParticleSimple.h"
#include "cpp/distribution/DistributionSimple.h"
#include "cpp/distribution/DistributionCircle.h"
#include "cpp/distribution/ParticleDistribution.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(std::vector<unsigned long> particleCounts, std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions);

	std::vector<Particle*> input() override;


private:
	std::vector<unsigned long> particleCounts;
	std::vector<std::shared_ptr<ParticleDistribution>> particleDistributions;
};
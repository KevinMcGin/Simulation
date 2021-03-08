#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "ParticleDistributionSimple.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(unsigned long particleCount, ParticleDistributionSimple particleDistribution);

	virtual vector<Particle*> input();



private:
	const unsigned long particleCount;
	ParticleDistributionSimple particleDistribution;
};
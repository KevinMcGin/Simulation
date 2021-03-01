#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"
#include "DistributionLine.h"
#include "DistributionCircle.h"
#include "ParticleDistributionSimple.h"

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(unsigned long particleCount) :
		particleCount(particleCount) {
		Distribution* massDistrubtion = new DistributionLine(1, 0.5);
		Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 10);
		Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 1);
		Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
		particleDistribution = new ParticleDistributionSimple(massDistrubtion, massDistrubtion, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
	}

	virtual vector<Particle*> input() {

		vector<Particle*> particles;
		for (unsigned long i = 0; i < particleCount; i++) {
			particles.push_back(particleDistribution->getParticle());
		}

		return particles;
	}



private:
	const unsigned long particleCount;
	ParticleDistributionSimple* particleDistribution;
};
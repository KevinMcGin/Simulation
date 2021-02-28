#pragma once
#include "SimulationInput.h"
#include "ParticleSimple.h"

#include <list>

class SimulationInputRandomSimple : public SimulationInput {
public:
	SimulationInputRandomSimple(unsigned long particleCount) :
		particleCount(particleCount) { srand (time(NULL)); }

	virtual list<Particle*> input() {
		double meanMass = 1;
		double deltaMass = .5;
		double meanPos = 0;
		double deltaPos = 10;
		double meanVel = 0;
		double deltaVel = 1;

		list<Particle*> particles;
		for (unsigned long i = 0; i < particleCount; i++) {
			//density is the same for all particles
			double mass = random(meanMass, deltaMass);
			particles.push_back( new ParticleSimple(mass, mass, 
				{ random(meanPos, deltaPos), random(meanPos, deltaPos), 0 },
				{ random(meanVel, deltaVel), random(meanVel, deltaVel), 0 },
				{ 0, 0, 0 }) );
		}

		return particles;
	}



private:
	const unsigned long particleCount;

	double random(double mean, double delta) {
		const double deltaRand = ((double)rand() / RAND_MAX)*2*delta - delta;
		return mean + deltaRand;
	}
};
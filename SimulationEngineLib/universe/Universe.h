#pragma once
#include <vector>
#include <memory>

#include "particle/Particle.cuh"
#include "universe/output/SimulationOutput.h"
#include "law/Law.h"


enum Usage { UNDEFINED, TRUE, FALSE };

class Universe {
public:
	Universe(
		vector<Particle*> particles, 
		vector<Law*> laws, 
		const shared_ptr<SimulationOutput> output, 
		unsigned int deltaTime,
		unsigned long endTime,
		Usage use_gpu = UNDEFINED
	);
	~Universe();
	vector<Particle*> particles;
	virtual void run() = 0;

protected:
	vector<Law*> laws;
	const shared_ptr<SimulationOutput> output;
	unsigned int deltaTime;
	unsigned long endTime;
	Usage use_gpu;
};
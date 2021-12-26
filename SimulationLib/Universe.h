#pragma once
#include <vector>
#include <memory>

#include "Particle.cuh"
#include "SimulationOutput.h"
#include "Law.h"


enum Usage { UNDEFINED, TRUE, FALSE };

class Universe {
public:
	Universe(vector<Particle*> particles, vector<Law*> laws, const shared_ptr<SimulationOutput> output, unsigned int deltaTime, unsigned long endTime);
	~Universe();
	vector<Particle*> particles;
	virtual void run() = 0;

protected:
	vector<Law*> laws;
	const shared_ptr<SimulationOutput> output;
	unsigned int deltaTime;
	unsigned long endTime;
	static Usage USE_GPU;
};
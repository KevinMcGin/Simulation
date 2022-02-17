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
		std::vector<Particle*> particles, 
		std::vector<Law*> laws, 
		const std::shared_ptr<SimulationOutput> output, 
		unsigned int deltaTime,
		unsigned long endTime,
		Usage useGpu = UNDEFINED
	);
	~Universe();
	std::vector<Particle*> particles;
	virtual void run() = 0;

protected:
	std::vector<Law*> laws;
	const std::shared_ptr<SimulationOutput> output;
	unsigned int deltaTime;
	unsigned long endTime;
	Usage useGpu;

private:
	void printUseGpu();
};
#pragma once
#include "shared/precision/Real.cuh"
#include <vector>
#include <memory>

#include "shared/particle/Particle.cuh"
#include "cpp/universe/output/SimulationOutput.h"
#include "cpp/law/Law.h"


enum Usage { UNDEFINED, TRUE, FALSE };

class Universe {
public:
	// deltaTime is how much simulated time one step advances, in seconds.
	// A Real rather than a whole number of seconds: the step is the run
	// length divided by the frames asked for, which is a fraction of a
	// second as soon as the run is short or the frame count high, and
	// truncating that to an integer either changes the run silently or
	// collapses it to a zero-length step.
	Universe(
		std::vector<Particle*> particles, 
		std::vector<std::shared_ptr<Law>> laws, 
		const std::shared_ptr<SimulationOutput> output, 
		Real deltaTime,
		unsigned long endTime,
		Usage useGpu = UNDEFINED
	);
	// Virtual so that deleting a universe through this base pointer still
	// runs the derived destructor, which owns the GPU data controller.
	virtual ~Universe();
	std::vector<Particle*> particles;
	virtual void run() = 0;

protected:
	std::vector<std::shared_ptr<Law>> laws;
	const std::shared_ptr<SimulationOutput> output;
	Real deltaTime;
	unsigned long endTime;
	Usage useGpu;

private:
	void printUseGpu();
};
#pragma once
#include "shared/precision/Real.cuh"

#include "cpp/universe/input/SimulationInputRandomSimple.h"

// One star at the centre of a disk of particles. Defaults are the values
// this used before any of it was configurable, so a caller that sets only
// what it cares about gets the same star system as before for the rest.
//
// A struct rather than a dozen positional floats: every one of them is a
// Real, so a pair swapped at a call site would build and run, quietly
// simulating something else.
struct StarSystemConfig {
	unsigned long particleCount = 10;

	// The star: its own mass and density, independent of the disk's.
	Real starMass = 50;
	Real starDensity = 1000;

	// The disk's particles. Each spread is a fraction of its mean — 0 makes
	// every particle identical, 0.9 varies them by up to 90% either way.
	Real meanMass = 0.01;
	Real massSpread = 0.9;
	Real meanDensity = 1000;
	Real densitySpread = 0;

	// Where the particles sit: the ring they fill, and where within it they
	// gather (0..1, 0.5 being an even spread).
	Real innerRadius = 0.5;
	Real outerRadius = 15;
	Real positionBias = 0.5;

	// The mass the disk's orbital velocities are calculated from. Separate
	// from starMass so a disk can be started on the orbits of a heavier or
	// lighter star than the one actually at its centre — which is how a
	// system is given somewhere to settle to, rather than starting in
	// balance.
	Real diskCentralMass = 50;
};

class SimulationInputDistributionStarSystem {
public:
	explicit SimulationInputDistributionStarSystem(StarSystemConfig config);

    std::unique_ptr<SimulationInputRandomSimple> getStarSystemDistribution();

private: 
    const StarSystemConfig config;
};

#pragma once

#include "cpp/universe/input/SimulationInputRandomSimple.h"


class SimulationInputDistributionStarSystem {
public:
	SimulationInputDistributionStarSystem(
        float meanMass,
        float meanDensity,
        float starMass,
        float outerRadius,
        unsigned long particleCount
    );

    std::unique_ptr<SimulationInputRandomSimple> getStarSystemDistribution();

private: 
    float meanMass;
    float meanDensity;
    float starMass;
    float outerRadius;
    unsigned long particleCount;
};
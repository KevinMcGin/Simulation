#include "Particle.h"
#include "ParticleSimple.h"
#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.h"
#include "DistributionValue.h"
#include "../src/DistributionMassDensity.h"

#include <stdio.h>

int main()
{
	Distribution* massDistrubtion = new DistributionSimple(0.001, 0.0009);
	Distribution* density = new DistributionValue(1);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistrubtion, density);
    Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 1);
    Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0.005);
    Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
    ParticleDistributionSimple particleDistribution(densityDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
    SimulationInput* input = new SimulationInputRandomSimple(500, particleDistribution);

    SimulationOutput* output = new SimulationOutputJSON();

    Universe* universe = new UniverseImplSimple(input, output, 100);

    universe->run();

    delete universe;
    return 0;
}
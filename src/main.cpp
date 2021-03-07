#include "Particle.h"
#include "ParticleSimple.h"
#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.h"

#include <stdio.h>

int main()
{
    Distribution* massDistrubtion = new DistributionSimple(0.1, 0.05);
    Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 1);
    Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0.005);
    Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
    ParticleDistributionSimple particleDistribution(massDistrubtion, massDistrubtion, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
    SimulationInput* input = new SimulationInputRandomSimple(500, particleDistribution);

    SimulationOutput* output = new SimulationOutputJSON();

    Universe* universe = new UniverseImplSimple(input, output, 100);

    universe->run();

    delete universe;
    return 0;
}
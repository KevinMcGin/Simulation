#include "Particle.h"
#include "ParticleSimple.h"
#include "SimulationInputSimple.h"
#include "SimulationOutputSimple.h"
#include "UniverseImplSimple.h"

#include <stdio.h>

int main()
{
    SimulationInput* input = new SimulationInputSimple();
    SimulationOutput* ouput = new SimulationOutputSimple();
    Universe* u = new UniverseImplSimple(input, ouput, 100L);
    u->run();
}
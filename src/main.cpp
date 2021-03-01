#include "Particle.h"
#include "ParticleSimple.h"
#include "SimulationInputRandomSimple.h"
#include "SimulationOutputSimple.h"
#include "UniverseImplSimple.h"

#include <stdio.h>

int main()
{
    SimulationInput* input = new SimulationInputRandomSimple(100);
    SimulationOutput* ouput = new SimulationOutputSimple();
    Universe* universe = new UniverseImplSimple(input, ouput, 1);
    universe->run();

    delete universe;
    return 0;
}
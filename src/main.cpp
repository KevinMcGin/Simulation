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
    Universe* u = new UniverseImplSimple(input, ouput, 1);
    u->run();
}
#pragma once
#include "particle/ParticleSimple.h"

class ParticleTestHelper {
public:
    static void expectParticlesEqual(vector<Particle*> particlesCpu, vector<Particle*> particlesGpu);
};
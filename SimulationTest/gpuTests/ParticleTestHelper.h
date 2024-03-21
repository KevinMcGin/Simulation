#pragma once
#include "cpp/particle/ParticleSimple.h"

class ParticleTestHelper {
public:
    static void expectParticlesEqual(std::vector<Particle*> particlesCpu, std::vector<Particle*> particlesGpu);
};
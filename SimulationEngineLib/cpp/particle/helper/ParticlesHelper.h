#pragma once
#include "shared/particle/Particle.cuh"

#include <vector>

class ParticlesHelper {
public:
    static bool removeDeletedParticles(std::vector<Particle*>& particles);
};
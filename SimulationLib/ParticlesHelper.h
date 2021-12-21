#pragma once
#include "Particle.cuh"

#include <vector>

class ParticlesHelper {
public:
    static bool removeDeletedParticles(vector<Particle*>& particles);
};
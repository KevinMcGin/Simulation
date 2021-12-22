#pragma once
#include "GpuDataController.cuh"
#include "ParticleSimple.h"
#include "Law.h"

class LawHelper {
public:
    static void runCpuLaw(Law* law, vector<Particle*>& particles, const int stepsCount = 1);
    static void runGpuLaw(Law* law, vector<Particle*>& particles, const int stepsCount = 1);
    static void expectGpuLikeCpu(Law* law, const int particleCount = 1, const int stepsCount = 1);
    static vector<Particle*> setupParticles(const int particleCount = 1);
};
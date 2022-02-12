#pragma once
#include "gpuHelper/GpuDataController.cuh"
#include "particle/ParticleSimple.h"
#include "law/Law.h"

class LawHelper {
public:
    static void runCpuLaw(Law* law, std::vector<Particle*>& particles, const int stepsCount = 1);
    static void runGpuLaw(Law* law, std::vector<Particle*>& particles, const int stepsCount = 1);
    static void expectGpuLikeCpu(Law* law, const int particleCount = 1, const int stepsCount = 1);
    static void expectGpuLikeCpuRounded(Law* law, const int particleCount = 1, const int stepsCount = 1);
    static std::vector<Particle*> setupParticles(const int particleCount = 1);
};
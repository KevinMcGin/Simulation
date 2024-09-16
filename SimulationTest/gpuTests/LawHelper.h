#pragma once
#include "cuda/gpuHelper/GpuDataController.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "cpp/law/Law.h"

class LawHelper {
public:
    static void runCpuLaw(std::shared_ptr<Law> law, std::vector<Particle*>& particles, const int stepsCount = 1);
    static void runGpuLaw(std::shared_ptr<Law> law, std::vector<Particle*>& particles, const int stepsCount = 1);
    static void expectGpuLikeCpu(std::shared_ptr<Law> law, const int particleCount = 1, const int stepsCount = 1);
    static void expectGpuLikeCpuRounded(
        std::unique_ptr<Law> law, 
        const int particleCount = 1, 
        const int stepsCount = 1, 
        const bool doAsserts = false
    );
    static std::vector<Particle*> setupParticles(const int particleCount = 1);
};
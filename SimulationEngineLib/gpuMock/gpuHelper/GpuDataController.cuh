#pragma once

#include <vector>

#include "shared/particle/Particle.cuh"

class GpuDataController {
public:
    GpuDataController();
    ~GpuDataController();
    void putParticlesOnDevice(std::vector<Particle*> particles, bool firstRun = false);
    void getParticlesFromDevice(std::vector<Particle*>& particles);
    Particle** get_td_par();
    int getParticleCount();
};
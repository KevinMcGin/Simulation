#pragma once
#include "shared/particle/Particle.cuh"
#include "cuda/gpuHelper/CudaWithError.cuh"

#include <vector>

class GpuDataController {
public:
    GpuDataController();
    ~GpuDataController();
    void putParticlesOnDevice(std::vector<Particle*> particles, bool firstRun = false);
    void getParticlesFromDevice(std::vector<Particle*>& particles);
    Particle** get_td_par();
    int getParticleCount();

private:
    Particle** d_par;
    Particle** td_par;
    int particleCount = 0;
    CudaWithError cudaWithError;
};
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
    void deleteParticlesOnDevice();
    Particle** get_td_par();
    int getParticleCount();

private:
    Particle** d_par = NULL;
    Particle** td_par = NULL;
    int particleCount = 0;
    CudaWithError cudaWithError;
};
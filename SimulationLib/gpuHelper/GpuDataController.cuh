#pragma once
#include "particle/Particle.cuh"
#include "gpuHelper/CudaWithError.cuh"

#include <vector>

class GpuDataController {
public:
    GpuDataController();
    ~GpuDataController();
    void putParticlesOnDevice(vector<Particle*> particles, bool firstRun = false);
    void getParticlesFromDevice(vector<Particle*>& particles);
    // Particle** get_d_par() { return d_par; }
    Particle** get_td_par() { return td_par; }
    int getParticleCount() { return particleCount; }

private:
    Particle** d_par;
    Particle** td_par;
    int particleCount = 0;
	CudaWithError* cudaWithError;
};
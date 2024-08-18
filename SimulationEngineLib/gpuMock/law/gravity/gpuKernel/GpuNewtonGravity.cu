#include "gpuMock/law/gravity/gpuKernel/GpuNewtonGravity.cuh"

GpuNewtonGravity::GpuNewtonGravity(
    float G,
    std::shared_ptr<MomentumService> momentumService
) : GpuLaw("GpuNewtonGravity") { }


void GpuNewtonGravity::run(
    Particle** particles, 
    int particleCount,
	unsigned int deltaTime
) {}


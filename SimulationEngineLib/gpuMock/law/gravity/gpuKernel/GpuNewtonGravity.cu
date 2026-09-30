#include "gpuMock/law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#include "gpuMock/gpuHelper/GpuMockUnreachable.cuh"

GpuNewtonGravity::GpuNewtonGravity(
    float G,
    std::shared_ptr<MomentumService> momentumService
) : GpuLaw("GpuNewtonGravity") { }


void GpuNewtonGravity::run(
    Particle** particles, 
    int particleCount,
	float deltaTime
) { gpuMockUnreachable("GpuNewtonGravity::run"); }


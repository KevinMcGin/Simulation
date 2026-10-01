#include "gpuMock/law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#include "shared/particle/Particle.cuh"
#include "gpuMock/gpuHelper/GpuMockUnreachable.cuh"

GpuNewtonFirstLaw::GpuNewtonFirstLaw() : GpuLaw("NewtonFirstLaw") { }

void GpuNewtonFirstLaw::run(
    Particle** particles, 
    int particleCount,
	Real deltaTime
) { gpuMockUnreachable("GpuNewtonFirstLaw::run"); }
 
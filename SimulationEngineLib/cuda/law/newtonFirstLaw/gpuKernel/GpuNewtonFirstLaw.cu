#include "cuda/law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#include "shared/particle/Particle.cuh"

GpuNewtonFirstLaw::GpuNewtonFirstLaw() : GpuLaw("NewtonFirstLaw") { }

__global__
static void advanceParticles(
	Particle** particles,
	int particleCount,
	float deltaTime
) {
	int particleIndex = threadIdx.x + blockIdx.x*blockDim.x;
	if (particleIndex < particleCount) { 
		particles[particleIndex]->advance(deltaTime);
	} 
}

void GpuNewtonFirstLaw::run(
	Particle** particles, 
	int particleCount,
	float deltaTime
) {
	cudaWithError->runKernel("advanceParticles", [&](unsigned int kernelSize) {
		advanceParticles <<<1 + particleCount/kernelSize, kernelSize>>> (
			particles,
			particleCount,
			deltaTime
		);
	});
}
 
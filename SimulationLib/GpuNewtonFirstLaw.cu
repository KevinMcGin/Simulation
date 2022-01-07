#include "GpuNewtonFirstLaw.cuh"
#include "Particle.cuh"

GpuNewtonFirstLaw::GpuNewtonFirstLaw() : GpuLaw("NewtonFirstLaw") { }

__global__ 
static void advanceParticles(Particle** particles, int particleCount) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < particleCount) { 
		particles[idx]->advance();
	} 
}

void GpuNewtonFirstLaw::run(Particle** td_par, int particleCount) {
	advanceParticles <<<1 + particleCount/256, 256>>> (td_par, particleCount);
	cudaWithError->peekAtLastError("advanceParticles");
}

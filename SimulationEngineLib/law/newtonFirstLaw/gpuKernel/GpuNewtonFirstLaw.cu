#include "law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#include "particle/Particle.cuh"

GpuNewtonFirstLaw::GpuNewtonFirstLaw() : GpuLaw("NewtonFirstLaw") { }

#if defined(USE_GPU) 
	__global__
	static void advanceParticles(Particle** particles, int particleCount) {
		int particleIndex = threadIdx.x + blockIdx.x*blockDim.x;
		if(particleIndex < particleCount) { 
			particles[particleIndex]->advance();
		} 
	}
#endif 

void GpuNewtonFirstLaw::run(Particle** particles, int particleCount) {
	#if defined(USE_GPU) 
		advanceParticles <<<1 + particleCount/256, 256>>> (particles, particleCount);
		cudaWithError->peekAtLastError("advanceParticles");
	#endif 
}

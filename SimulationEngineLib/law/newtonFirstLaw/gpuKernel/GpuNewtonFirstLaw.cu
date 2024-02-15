#include "law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#include "particle/Particle.cuh"

GpuNewtonFirstLaw::GpuNewtonFirstLaw() : GpuLaw("NewtonFirstLaw") { }

#if defined(USE_GPU) 
	__global__
	static void advanceParticles(Particle** particles, int particleCount) {
		int particleIndex = threadIdx.x + blockIdx.x*blockDim.x;
		if (particleIndex < particleCount) { 
			particles[particleIndex]->advance();
		} 
	}
#endif 

void GpuNewtonFirstLaw::run(Particle** particles, int particleCount) {
	#if defined(USE_GPU) 
		cudaWithError->runKernel("advanceParticles", [&](unsigned int kernelSize) {
			advanceParticles <<<1 + particleCount/kernelSize, kernelSize>>> (particles, particleCount);
		});
	#endif 
}
 
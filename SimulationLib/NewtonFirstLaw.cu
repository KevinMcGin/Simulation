#include "NewtonFirstLaw.cuh"
#include "Particle.cuh"

NewtonFirstLaw::NewtonFirstLaw() : Law("NewtonFirstLaw") { }


__global__ 
static void advanceParticles(Particle** particles, int particleCount) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < particleCount) { 
		particles[idx]->position = particles[idx]->position + particles[idx]->velocity;
	} 
}

void NewtonFirstLaw::cpuRun(vector<Particle*>& particles) {
	for (const auto& p : particles)
		p->advance();
}

void NewtonFirstLaw::gpuRun(Particle** td_par, int particleCount) {
	advanceParticles <<<1 + particleCount/256, 256>>> (td_par, particleCount);
	cudaWithError->deviceSynchronize();
}

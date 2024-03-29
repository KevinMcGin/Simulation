#include "cuda/gpuHelper/GpuDataController.cuh"
#include "cpp/particle/ParticleSimple.h"


GpuDataController::GpuDataController() : cudaWithError(CudaWithError("GpuDataController")) {
	cudaWithError.setDevice(0);
}

GpuDataController::~GpuDataController() {
	for(int i = 0; i < particleCount; i++) {
		cudaWithError.free(d_par[i]);
	}
	cudaWithError.free(td_par);
	delete d_par;
}

void GpuDataController::putParticlesOnDevice(std::vector<Particle*> particles, bool firstRun) {
	if (!firstRun) {
		for(int i = 0; i < particleCount; i++) {
			cudaWithError.free(d_par[i]);
		}
		cudaWithError.free(td_par);
		delete d_par;
	}
	
	particleCount = (int)particles.size();

	//Copy dynamically allocated child objects to GPU
	d_par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i) {
		cudaWithError.malloc((void**)&d_par[i], sizeof(*particles[i]));
		cudaWithError.memcpy(d_par[i], particles[i], sizeof(*particles[i]), cudaMemcpyHostToDevice);
	}

	//Copy the d_par array itself to the device
	cudaWithError.malloc((void**)&td_par, particleCount * sizeof(Particle*));
	cudaWithError.memcpy(td_par, d_par, particleCount * sizeof(Particle*), cudaMemcpyHostToDevice);
}

void GpuDataController::getParticlesFromDevice(std::vector<Particle*>& particles) {
	cudaWithError.deviceSynchronize("getParticlesFromDevice");
	for(int i = 0; i < particleCount; i++) {
		cudaWithError.memcpy(particles[i], d_par[i], sizeof(*particles[i]), cudaMemcpyDeviceToHost);
	}
	if (particleCount < particles.size()) {
		particles.erase (particles.begin() + particleCount, particles.end());
	}
}

__global__
static void deleteParticle(
	Particle** particles,
	int* particleCount
) {
	int particleIndex = threadIdx.x + blockIdx.x*blockDim.x;
	printf("particleCount: %d", *particleCount);
	if (particleIndex < *particleCount) { 
		if (particles[particleIndex]->deleted) {
			int lastParticleIndex = *particleCount - 1;
			printf("lastParticleIndex: %d", lastParticleIndex);
			if (particleIndex < lastParticleIndex) {
				// particles[particleIndex] = particles[lastParticleIndex];
			}
			// particles[lastParticleIndex] = nullptr;
			(*particleCount)--;
		}
	} 
}

void GpuDataController::deleteParticlesOnDevice() {
	int* gpuParticleCount = NULL;
	cudaWithError.malloc((void**)&gpuParticleCount, sizeof(particleCount));
	cudaWithError.memcpy(gpuParticleCount, &particleCount, sizeof(particleCount), cudaMemcpyHostToDevice);

	int blockSize = 1;
	int numBlocks = particleCount;

	std::cout << "cpu: particleCount: " << particleCount;
	cudaWithError.runKernel("deleteParticlesOnDevice", [&](unsigned int kernelSize) {
		deleteParticle<<<numBlocks, blockSize>>>(td_par, gpuParticleCount);
	});
	
	cudaWithError.memcpy(&particleCount, gpuParticleCount, sizeof(particleCount), cudaMemcpyDeviceToHost);
	
	cudaWithError.free(gpuParticleCount);
}

Particle** GpuDataController::get_td_par() { return td_par; }
int GpuDataController::getParticleCount() { return particleCount; }


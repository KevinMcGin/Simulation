#include "gpuHelper/GpuDataController.cuh"
#include "particle/ParticleSimple.h"

GpuDataController::GpuDataController() {
    cudaWithError = new CudaWithError("GpuDataController");
    cudaWithError->setDevice(0);
}

GpuDataController::~GpuDataController() {
    delete cudaWithError;
	for(int i = 0; i < particleCount; i++) {
		cudaWithError->free(d_par[i]);
	}
	cudaWithError->free(td_par);
	delete d_par;
}

void GpuDataController::putParticlesOnDevice(vector<Particle*> particles, bool firstRun) {
	if(!firstRun) {
		for(int i = 0; i < particleCount; i++) {
			cudaWithError->free(d_par[i]);
		}
		cudaWithError->free(td_par);
		delete d_par;
	}
	
	particleCount = (int)particles.size();

	//Copy dynamically allocated child objects to GPU
	d_par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i) {
		cudaWithError->malloc((void**)&d_par[i], sizeof(*particles[i]));
		cudaWithError->memcpy(d_par[i], particles[i], sizeof(*particles[i]), cudaMemcpyHostToDevice);
	}

	//Copy the d_par array itself to the device
	cudaWithError->malloc((void**)&td_par, particleCount * sizeof(Particle*));
	cudaWithError->memcpy(td_par, d_par, particleCount * sizeof(Particle*), cudaMemcpyHostToDevice);
}

void GpuDataController::getParticlesFromDevice(vector<Particle*>& particles) {
	cudaWithError->deviceSynchronize();
	for(int i = 0; i < particleCount; i++) {
		cudaWithError->memcpy(particles[i], d_par[i], sizeof(*particles[i]), cudaMemcpyDeviceToHost);
	}
}


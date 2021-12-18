#include "GpuDataController.cuh"
#include "CudaWithError.cuh"
#include "ParticleSimple.h"

GpuDataController::GpuDataController() {
    cudaWithError = new CudaWithError("GpuDataController");
    cudaWithError->setDevice(0);
}

GpuDataController::~GpuDataController() {
    delete cudaWithError;
}

void GpuDataController::putParticlesOnDevice(vector<Particle*> particles) {
	particleCount = (int)particles.size();
    
    //Instantiate object on the CPU
	auto particlesArray = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i)
		particlesArray[i] = particles[i];

	//Copy dynamically allocated child objects to GPU
	d_par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i) {
		cudaWithError->malloc((void**)&d_par[i], sizeof(ParticleSimple));
		cudaWithError->memcpy(d_par[i], particlesArray[i], sizeof(ParticleSimple), cudaMemcpyHostToDevice);
	}

	//Copy the d_par array itself to the device
	cudaWithError->malloc((void**)&td_par, particleCount * sizeof(Particle *));
	cudaWithError->memcpy(td_par, d_par, particleCount * sizeof(Particle *), cudaMemcpyHostToDevice);

    delete particlesArray;
}

void GpuDataController::getParticlesFromDevice(vector<Particle*>& particles) {
	int particleCount = (int)particles.size();

	//copy particles back to cpu
	for(int i = 0; i < particleCount; i++) {
        //TODO Is using the vector particles here ok?
		cudaWithError->memcpy(particles[i] ,d_par[i], sizeof(ParticleSimple), cudaMemcpyDeviceToHost);
		cudaWithError->free(d_par[i]);
	}
	cudaWithError->free(td_par);
	delete d_par;
}


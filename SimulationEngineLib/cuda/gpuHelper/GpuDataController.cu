#include "cuda/gpuHelper/GpuDataController.cuh"
#include "cpp/particle/ParticleSimple.h"

#if defined(USE_GPU)
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
		cudaWithError.deviceSynchronize();
		for(int i = 0; i < particleCount; i++) {
			cudaWithError.memcpy(particles[i], d_par[i], sizeof(*particles[i]), cudaMemcpyDeviceToHost);
		}
	}


	Particle** GpuDataController::get_td_par() { return td_par; }
	int GpuDataController::getParticleCount() { return particleCount; }

#else
	GpuDataController::GpuDataController() : cudaWithError(CudaWithError("GpuDataController")) {};
	GpuDataController::~GpuDataController() = default;

	void GpuDataController::putParticlesOnDevice(std::vector<Particle*> particles, bool firstRun) {}

	void GpuDataController::getParticlesFromDevice(std::vector<Particle*>& particles) {}

	Particle** GpuDataController::get_td_par() { return td_par; }
	int GpuDataController::getParticleCount() { return particleCount; }
#endif


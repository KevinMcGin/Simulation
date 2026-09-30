#include "gpuMock/gpuHelper/GpuDataController.cuh"
#include "gpuMock/gpuHelper/GpuMockUnreachable.cuh"

	GpuDataController::GpuDataController() {};
	GpuDataController::~GpuDataController() = default;

	void GpuDataController::putParticlesOnDevice(std::vector<Particle*> particles, bool firstRun) { gpuMockUnreachable("GpuDataController::putParticlesOnDevice"); }

	void GpuDataController::getParticlesFromDevice(std::vector<Particle*>& particles) { gpuMockUnreachable("GpuDataController::getParticlesFromDevice"); }

	void GpuDataController::deleteParticlesOnDevice() { gpuMockUnreachable("GpuDataController::deleteParticlesOnDevice"); }

	Particle** GpuDataController::get_td_par() { gpuMockUnreachable("GpuDataController::get_td_par"); }
	int GpuDataController::getParticleCount() { gpuMockUnreachable("GpuDataController::getParticleCount"); }

#include "gpuMock/gpuHelper/GpuDataController.cuh"

	GpuDataController::GpuDataController() {};
	GpuDataController::~GpuDataController() = default;

	void GpuDataController::putParticlesOnDevice(std::vector<Particle*> particles, bool firstRun) {}

	void GpuDataController::getParticlesFromDevice(std::vector<Particle*>& particles) {}

	Particle** GpuDataController::get_td_par() { return nullptr; }
	int GpuDataController::getParticleCount() { return NULL; }


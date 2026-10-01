// The gpuMock sources are only compiled into the library in a CPU-only
// build; in a GPU build the real CUDA classes take their place, so there is
// nothing here to test (and the mock headers would clash with the real
// ones).
#if !defined(USE_GPU)

#include  <gtest/gtest.h>

#include "gpuMock/gpuHelper/CudaWithError.cuh"
#include "gpuMock/gpuHelper/GpuDataController.cuh"
#include "gpuMock/law/collision/gpuKernel/GpuCollision.cuh"
#include "gpuMock/law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#include "gpuMock/law/newtonFirstLaw/gpuKernel/GpuNewtonFirstLaw.cuh"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"

#include <stdexcept>

TEST(GpuMockTest, CudaWithErrorThrows) {
	CudaWithError cudaWithError("GpuMockTest");
	void* devPtr = nullptr;

	EXPECT_THROW(cudaWithError.setDevice(0), std::runtime_error);
	EXPECT_THROW(cudaWithError.resetDevice(), std::runtime_error);
	EXPECT_THROW(cudaWithError.malloc(&devPtr, 1), std::runtime_error);
	EXPECT_THROW(cudaWithError.memcpy(nullptr, nullptr, 0, {}), std::runtime_error);
	EXPECT_THROW(cudaWithError.deviceSynchronize("GpuMockTest"), std::runtime_error);
	EXPECT_THROW(cudaWithError.free(devPtr), std::runtime_error);
	EXPECT_THROW(cudaWithError.peekAtLastError("GpuMockTest"), std::runtime_error);
	EXPECT_THROW(cudaWithError.getFreeGpuMemory(), std::runtime_error);
	EXPECT_THROW(cudaWithError.getMaxThreads(), std::runtime_error);
	EXPECT_THROW(cudaWithError.runKernel("GpuMockTest", [](unsigned int) {}), std::runtime_error);
	EXPECT_THROW(CudaWithError::setMinMemoryRemaining(0), std::runtime_error);
	EXPECT_THROW(CudaWithError::setMaxMemoryPerEvent(0), std::runtime_error);
	EXPECT_THROW(CudaWithError::setKernelSize(0), std::runtime_error);
}

TEST(GpuMockTest, GpuDataControllerThrows) {
	GpuDataController gpuDataController = GpuDataController();
	std::vector<Particle*> particles = {};

	EXPECT_THROW(gpuDataController.putParticlesOnDevice(particles, true), std::runtime_error);
	EXPECT_THROW(gpuDataController.getParticlesFromDevice(particles), std::runtime_error);
	EXPECT_THROW(gpuDataController.deleteParticlesOnDevice(), std::runtime_error);
	EXPECT_THROW(gpuDataController.get_td_par(), std::runtime_error);
	EXPECT_THROW(gpuDataController.getParticleCount(), std::runtime_error);
}

TEST(GpuMockTest, GpuLawsThrow) {
	auto momentumService = std::make_shared<NewtonMomentumService>();
	Particle** particles = nullptr;

	GpuNewtonFirstLaw newtonFirstLaw = GpuNewtonFirstLaw();
	EXPECT_THROW(newtonFirstLaw.run(particles, 0, 1.0), std::runtime_error);

	GpuNewtonGravity newtonGravity = GpuNewtonGravity(1.0, momentumService);
	EXPECT_THROW(newtonGravity.run(particles, 0, 1.0), std::runtime_error);

	GpuCollision collision = GpuCollision(nullptr, nullptr, momentumService);
	EXPECT_THROW(collision.run(particles, 0, 1.0), std::runtime_error);
}

// Building the laws is not itself the misconfiguration: a CPU-only run
// still constructs a GpuLaw for every Law it holds, and never runs them.
TEST(GpuMockTest, ConstructingAGpuLawDoesNotThrow) {
	EXPECT_NO_THROW(GpuNewtonFirstLaw());
	EXPECT_NO_THROW(GpuNewtonGravity(1.0, std::make_shared<NewtonMomentumService>()));
}

#endif

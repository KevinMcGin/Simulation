#include "law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "law/gravity/helper/GpuNewtonGravityHelper.cuh"

#include <cmath>
#include <algorithm>

GpuNewtonGravity::GpuNewtonGravity(float G) : GpuLaw("GpuNewtonGravity"), G(G) { }

__global__ 
void radiusComponentKernel(Particle** particles, Vector3D<float>* accelerations, unsigned long long betweenParticlesTriangularCount, float G, unsigned long long vectorsProcessedTriangular) {
	unsigned long long betweenParticlesTriangularIndex = threadIdx.x + blockIdx.x*blockDim.x;
	if(betweenParticlesTriangularIndex < betweenParticlesTriangularCount) { 
		radiusComponentKernelHelper(betweenParticlesTriangularIndex, particles, accelerations, betweenParticlesTriangularCount, G, vectorsProcessedTriangular);
	} 
}

__global__ 
void addAccelerationsKernelLower(Particle** particles, Vector3D<float>* accelerations, unsigned long long particleIndex2, unsigned long long vectorsProcessedTriangular) {
	unsigned long long particleIndex1 = threadIdx.x + blockIdx.x*blockDim.x;
	addAccelerationsKernelLowerHelper(particleIndex1, particles, accelerations, particleIndex2, vectorsProcessedTriangular);
}

__global__ 
void addAccelerationsKernelUpper(Particle** particles, Vector3D<float>* accelerations, unsigned long long xOffset, unsigned long long particleIndex2, unsigned long long particleCount, unsigned long long vectorsProcessedTriangular, unsigned long long betweenParticlesTriangularCount) {
	unsigned long long particleIndex1 = threadIdx.x + blockIdx.x*blockDim.x;
	addAccelerationsKernelUpperHelper(particleIndex1, particles, accelerations, xOffset, particleIndex2, particleCount, vectorsProcessedTriangular, betweenParticlesTriangularCount);
}

unsigned long long getRowsFromRowsAndColsCountMinusIdentity(unsigned long long rowsAndColsCount) {
	return 0.5 * (sqrt(4 * rowsAndColsCount + 1) + 1);
}

unsigned long long getRowsAndColsCountMinusIdentityFromRows(unsigned long long rowsAndColsCountMinusIdentityowsAndColsCount) {
	return (rowsAndColsCountMinusIdentityowsAndColsCount - 1) * rowsAndColsCountMinusIdentityowsAndColsCount;
}

void GpuNewtonGravity::run(Particle** particles, int particleCount) {
	unsigned long long betweenParticlesCount = ((unsigned long long)particleCount-1)*particleCount;
	Vector3D<float>* accelerations = NULL;
	
	long long freeGpuMemory = cudaWithError->getFreeGpuMemory();
	unsigned long long vector3DSize = sizeof(Vector3D<float>);
	long long maxVectorsAllocatableStage1 = freeGpuMemory / vector3DSize;
	long long maxVectorsAllocatable = std::min(maxVectorsAllocatableStage1, (long long)betweenParticlesCount);
	if(maxVectorsAllocatable <= 0) {
		throw std::runtime_error("Ran out of GPU memory");
	}

	cudaWithError->malloc((void**)&accelerations, maxVectorsAllocatable * sizeof(Vector3D<float>));

	unsigned long long particlesProcessed = 0;
	unsigned long long vectorsProcessed = 0;
	while(particlesProcessed < particleCount) {
		unsigned long long particlesProcessable = std::min(
			getRowsFromRowsAndColsCountMinusIdentity(vectorsProcessed + maxVectorsAllocatable),
			(unsigned long long)particleCount
		) - (vectorsProcessed > 0 ? getRowsFromRowsAndColsCountMinusIdentity(vectorsProcessed) : 0);
		if(particlesProcessable == 0) { 
			std::cout << "GPU can not run these many particles in Gravity\n";
			throw std::runtime_error("GPU can not run these many particles in Gravity");
		}
		unsigned long long vectorsProcessable = getRowsAndColsCountMinusIdentityFromRows(particlesProcessed + particlesProcessable) - getRowsAndColsCountMinusIdentityFromRows(particlesProcessed);
		unsigned long long vectorsProcessableTriangular = vectorsProcessable / 2;
		const unsigned int threadCount = 256;

		radiusComponentKernel <<<1 + vectorsProcessableTriangular/threadCount, threadCount>>> (particles, accelerations, vectorsProcessableTriangular, G, vectorsProcessed / 2);
		cudaWithError->peekAtLastError("radiusComponentKernel");

		for(int particleIndex = 0; particleIndex < particlesProcessed; particleIndex++) {
			addAccelerationsKernelUpper <<<1 + particlesProcessable / threadCount, threadCount>>> (
				particles, accelerations, std::max((int)particlesProcessed - particleIndex - 1, 0), particleIndex, particlesProcessed + particlesProcessable, vectorsProcessed / 2, vectorsProcessableTriangular
			);
			cudaWithError->peekAtLastError("addAccelerationsKernelUpper");
		}
		for(int particleIndex = particlesProcessed; particleIndex < particlesProcessable + particlesProcessed; particleIndex++) {
			addAccelerationsKernelLower <<<1 + particleIndex/threadCount, threadCount>>> (particles, accelerations, particleIndex, vectorsProcessed / 2);
			cudaWithError->peekAtLastError("addAccelerationsKernelLower");
			addAccelerationsKernelUpper <<<1 + particlesProcessable / threadCount, threadCount>>> (
				particles, accelerations, 0, particleIndex, particlesProcessed + particlesProcessable, vectorsProcessed / 2, vectorsProcessableTriangular
			);
			cudaWithError->peekAtLastError("addAccelerationsKernelUpper");
		}

		particlesProcessed += particlesProcessable;
		vectorsProcessed += vectorsProcessable;
	}
	
	cudaWithError->free(accelerations);
}


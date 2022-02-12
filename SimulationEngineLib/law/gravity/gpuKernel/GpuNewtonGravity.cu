#include "law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "law/gravity/helper/GpuNewtonGravityHelper.cuh"

#include <cmath>
#include <algorithm>

GpuNewtonGravity::GpuNewtonGravity(double G) : GpuLaw("GpuNewtonGravity"), G(G) { }

__global__ 
void radiusComponentKernel(Particle** particles, Vector3D* accelerations, unsigned long long n, double G, unsigned long long vectorsProcessedTriangular) {
	unsigned long long idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		radiusComponentKernelHelper(idx, particles, accelerations, n, G, vectorsProcessedTriangular);
	} 
}

__global__ 
void addAccelerationsKernelLower(Particle** particles, Vector3D* accelerations, unsigned long long x0, unsigned long long y, unsigned long long n, unsigned long long vectorsProcessedTriangular) {
	unsigned long long idx = threadIdx.x + blockIdx.x*blockDim.x;
	addAccelerationsKernelLowerHelper(idx, particles, accelerations, x0, y, n, vectorsProcessedTriangular);
}

__global__ 
void addAccelerationsKernelUpper(Particle** particles, Vector3D* accelerations, unsigned long long x0, unsigned long long y, unsigned long long n, unsigned long long vectorsProcessedTriangular, unsigned long long particlesProcessed, unsigned long long betweenParticlesTriangularCount) {
	unsigned long long idx = threadIdx.x + blockIdx.x*blockDim.x;
	addAccelerationsKernelUpperHelper(idx, particles, accelerations, x0, y, n, vectorsProcessedTriangular, particlesProcessed, betweenParticlesTriangularCount);
}

unsigned long long getRowsFromRowsAndColsCountMinusIdentity(unsigned long long rowsAndColsCount) {
	return 0.5 * (sqrt(4 * rowsAndColsCount + 1) + 1);
}

unsigned long long getRowsAndColsCountMinusIdentityFromRows(unsigned long long rowsAndColsCountMinusIdentityowsAndColsCount) {
	return (rowsAndColsCountMinusIdentityowsAndColsCount - 1) * rowsAndColsCountMinusIdentityowsAndColsCount;
}

void GpuNewtonGravity::run(Particle** td_par, int particleCount) {
	//Radius component
	unsigned long long betweenParticlesCount = ((unsigned long long)particleCount-1)*particleCount;
	Vector3D* accelerations = NULL;
	
	unsigned long long freeGpuMemory = cudaWithError->getFreeGpuMemory();
	unsigned long long vector3DSize = sizeof(Vector3D);
	unsigned long long maxVectorsAllocatableStage1 = freeGpuMemory / vector3DSize;
	unsigned long long maxVectorsAllocatable = std::min(maxVectorsAllocatableStage1, betweenParticlesCount);

	cudaWithError->malloc((void**)&accelerations, maxVectorsAllocatable * sizeof(Vector3D));

	unsigned long long particlesProcessed = 0;
	unsigned long long vectorsProcessed = 0;
	while(particlesProcessed < particleCount) {
		unsigned long long particlesProcessable = std::min(
			getRowsFromRowsAndColsCountMinusIdentity(vectorsProcessed + maxVectorsAllocatable),
			(unsigned long long)particleCount
		) - (vectorsProcessed > 0 ? getRowsFromRowsAndColsCountMinusIdentity(vectorsProcessed) : 0);
		if(particlesProcessable == 0) { 
			std::cout << "GPU can not run these many particles in Gravity\n";
			throw new std::runtime_error("GPU can not run these many particles in Gravity");
		}
		unsigned long long vectorsProcessable = getRowsAndColsCountMinusIdentityFromRows(particlesProcessed + particlesProcessable) - getRowsAndColsCountMinusIdentityFromRows(particlesProcessed);
		unsigned long long vectorsProcessableTriangular = vectorsProcessable / 2;

		radiusComponentKernel <<<1 + vectorsProcessableTriangular/256, 256>>> (td_par, accelerations, vectorsProcessableTriangular, G, vectorsProcessed / 2);
		cudaWithError->peekAtLastError("radiusComponentKernel");

		for(int i = particlesProcessed; i < particlesProcessable + particlesProcessed; i++) {
			addAccelerationsKernelLower <<<1 + i/256, 256>>> (td_par, accelerations, 0, i, i,  vectorsProcessed / 2);
			cudaWithError->peekAtLastError("addAccelerationsKernelLower");
			addAccelerationsKernelUpper <<<1 + (particleCount - 1 - i) / 256, 256>>> (
				td_par, accelerations, i + 1, i, particlesProcessed + particlesProcessable,  vectorsProcessed / 2, particlesProcessed, vectorsProcessableTriangular
			);
		}

		particlesProcessed += particlesProcessable;
		vectorsProcessed += vectorsProcessable;
	}
	
	cudaWithError->free(accelerations);
}


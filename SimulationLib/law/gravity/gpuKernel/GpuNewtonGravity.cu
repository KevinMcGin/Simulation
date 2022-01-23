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
void radiusComponentKernel(Particle** particles, Vector3D* accelerations, int n, double G, int vectorsProcessedTriangular) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		radiusComponentKernelHelper(idx, particles, accelerations, n, G, vectorsProcessedTriangular);
	} 
}

__global__ 
void addAccelerationsKernelLower(Particle** particles, Vector3D* accelerations, int x0, int y, int n, int vectorsProcessedTriangular) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	addAccelerationsKernelLowerHelper(idx, particles, accelerations, x0, y, n, vectorsProcessedTriangular);
}

__global__ 
void addAccelerationsKernelUpper(Particle** particles, Vector3D* accelerations, int x0, int y, int n, int vectorsProcessedTriangular, int particlesProcessed, int betweenParticlesTriangularCount) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	addAccelerationsKernelUpperHelper(idx, particles, accelerations, x0, y, n, vectorsProcessedTriangular, particlesProcessed, betweenParticlesTriangularCount);
}

unsigned long getRowsFromRowsAndColsCountMinusIdentity(unsigned long rowsAndColsCount) {
	return 0.5 * (sqrt(4 * rowsAndColsCount + 1) + 1);
}

unsigned long getRowsAndColsCountMinusIdentityFromRows(unsigned long rowsAndColsCountMinusIdentityowsAndColsCount) {
	return (rowsAndColsCountMinusIdentityowsAndColsCount - 1) * rowsAndColsCountMinusIdentityowsAndColsCount;
}

void GpuNewtonGravity::run(Particle** td_par, int particleCount) {
	//Radius component
	unsigned long betweenParticlesCount = (particleCount-1)*particleCount;
	Vector3D* accelerations = NULL;
	
	unsigned long freeGpuMemory = cudaWithError->getFreeGpuMemory();
	unsigned long vector3DSize = sizeof(Vector3D);
	unsigned long maxVectorsAllocatableStage1 = freeGpuMemory / vector3DSize;
	unsigned long maxVectorsAllocatable = std::min(maxVectorsAllocatableStage1, betweenParticlesCount);

	cudaWithError->malloc((void**)&accelerations, maxVectorsAllocatable * sizeof(Vector3D));

	unsigned long particlesProcessed = 0;
	unsigned long vectorsProcessed = 0;
	while(particlesProcessed < particleCount) {
		unsigned long particlesProcessable = std::min(
			getRowsFromRowsAndColsCountMinusIdentity(vectorsProcessed + maxVectorsAllocatable),
			(unsigned long)particleCount
		) - (vectorsProcessed > 0 ? getRowsFromRowsAndColsCountMinusIdentity(vectorsProcessed) : 0);
		if(particlesProcessable == 0) { 
			cout << "GPU can not run these many particles in Gravity\n";
			throw new runtime_error("GPU can not run these many particles in Gravity");
		}
		unsigned long vectorsProcessable = getRowsAndColsCountMinusIdentityFromRows(particlesProcessed + particlesProcessable) - getRowsAndColsCountMinusIdentityFromRows(particlesProcessed);
		unsigned long vectorsProcessableTriangular = vectorsProcessable / 2;

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


#include "law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#include "particle/ParticleSimple.h"
#include "particle/Particle.cuh"
#include "util/MatrixMaths.cuh"
#include "law/gravity/helper/NewtonGravityHelper.cuh"
#include "law/gravity/helper/GpuNewtonGravityHelper.cuh"

#include <cmath>
#include <algorithm>

GpuNewtonGravity::GpuNewtonGravity(float G) : GpuLaw("GpuNewtonGravity"), G(G) { }

#if defined(USE_GPU) 
	__global__
	void radiusComponentKernel(Particle** particles, Vector3D<float>* accelerations, unsigned long long betweenParticlesTriangularCount, float G, unsigned long long vectorsProcessedTriangular) {
		unsigned long long betweenParticlesTriangularIndex = threadIdx.x + blockIdx.x*blockDim.x;
		if (betweenParticlesTriangularIndex < betweenParticlesTriangularCount) { 
			radiusComponentKernelHelper(betweenParticlesTriangularIndex, particles, accelerations, betweenParticlesTriangularCount, G, vectorsProcessedTriangular);
		} 
	}
#endif 

#if defined(USE_GPU) 
	__global__
	void addAccelerationsKernelLower(Particle** particles, Vector3D<float>* accelerations, unsigned long long particleIndex2, unsigned long long vectorsProcessedTriangular) {
		unsigned long long particleIndex1 = threadIdx.x + blockIdx.x*blockDim.x;
		addAccelerationsKernelLowerHelper(particleIndex1, particles, accelerations, particleIndex2, vectorsProcessedTriangular);
	}
#endif 

#if defined(USE_GPU) 
	__global__
	void addAccelerationsKernelUpper(Particle** particles, Vector3D<float>* accelerations, unsigned long long xOffset, unsigned long long particleIndex2, unsigned long long particleCount, unsigned long long vectorsProcessedTriangular, unsigned long long betweenParticlesTriangularCount) {
		unsigned long long particleIndex1 = threadIdx.x + blockIdx.x*blockDim.x;
		addAccelerationsKernelUpperHelper(particleIndex1, particles, accelerations, xOffset, particleIndex2, particleCount, vectorsProcessedTriangular, betweenParticlesTriangularCount);
	}
#endif 

unsigned long long getRowsFromRowsAndColsCountMinusIdentity(unsigned long long rowsAndColsCount) {
	return 0.5 * (sqrt(4 * rowsAndColsCount + 1) + 1);
}

unsigned long long getRowsAndColsCountMinusIdentityFromRows(unsigned long long rowsAndColsCountMinusIdentityowsAndColsCount) {
	return (rowsAndColsCountMinusIdentityowsAndColsCount - 1) * rowsAndColsCountMinusIdentityowsAndColsCount;
}

void GpuNewtonGravity::run(Particle** particles, int particleCount) {
	#if defined(USE_GPU) 
		unsigned long long betweenParticlesCount = ((unsigned long long)particleCount-1)*particleCount;
		Vector3D<float>* accelerations = NULL;
		
		const double maxFractionMemoryAllocatable = 0.5;
		const long long freeGpuMemoryStage1 = cudaWithError->getFreeGpuMemory();
		const long long freeGpuMemory = (long long)(freeGpuMemoryStage1 * maxFractionMemoryAllocatable);
		const unsigned long long vector3DSize = sizeof(Vector3D<float>);
		const long long maxVectorsAllocatableStage1 = freeGpuMemory / vector3DSize;
		const long long maxVectorsAllocatable = std::min(maxVectorsAllocatableStage1, (long long)betweenParticlesCount);
		if (maxVectorsAllocatable <= 0) {
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
			if (particlesProcessable == 0) { 
				std::cout << "GPU can not run these many particles in Gravity\n";
				throw std::runtime_error("GPU can not run these many particles in Gravity");
			}
			unsigned long long vectorsProcessable = getRowsAndColsCountMinusIdentityFromRows(particlesProcessed + particlesProcessable) - getRowsAndColsCountMinusIdentityFromRows(particlesProcessed);
			unsigned long long vectorsProcessableTriangular = vectorsProcessable / 2;
			
			cudaWithError->runKernel("radiusComponentKernel", [&](unsigned int kernelSize) {
				radiusComponentKernel <<<1 + vectorsProcessableTriangular / kernelSize, kernelSize>>> (particles, accelerations, vectorsProcessableTriangular, G, vectorsProcessed / 2);
			});
			for(int particleIndex = 0; particleIndex < particlesProcessed; particleIndex++) {
				cudaWithError->runKernel("addAccelerationsKernelUpper", [&](unsigned int kernelSize) {
					addAccelerationsKernelUpper <<<1 + particlesProcessable / kernelSize, kernelSize>>> (
						particles, accelerations, std::max((int)particlesProcessed - particleIndex - 1, 0), particleIndex, particlesProcessed + particlesProcessable, vectorsProcessed / 2, vectorsProcessableTriangular
					);				
				});
			}
			for(int particleIndex = particlesProcessed; particleIndex < particlesProcessable + particlesProcessed; particleIndex++) {
				cudaWithError->runKernel("addAccelerationsKernelLower", [&](unsigned int kernelSize) {
					addAccelerationsKernelLower <<<1 + particleIndex / kernelSize, kernelSize>>> (particles, accelerations, particleIndex, vectorsProcessed / 2);				
				});
				cudaWithError->runKernel("addAccelerationsKernelUpper", [&](unsigned int kernelSize) {
					addAccelerationsKernelUpper <<<1 + particlesProcessable / kernelSize, kernelSize>>> (
						particles, accelerations, 0, particleIndex, particlesProcessed + particlesProcessable, vectorsProcessed / 2, vectorsProcessableTriangular
					);				
				});
			}

			particlesProcessed += particlesProcessable;
			vectorsProcessed += vectorsProcessable;
		}
		
		cudaWithError->free(accelerations);
	#endif 
}


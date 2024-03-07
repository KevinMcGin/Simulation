#include "cuda/law/collision/gpuKernel/GpuCollision.cuh"
#include "cuda/law/collision/helper/GpuCollisionHelper.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "shared/law/collision/detector/CollisionDetectorSimple.cuh"
#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "shared/util/MatrixMaths.cuh"

#include <assert.h>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <typeinfo>

//Cuda doesn't recognise virtual functions of classes initialised on the CPU, so we have to initialise them here
#if defined(USE_GPU) 
	__global__
	void setCollisionDetector(CollisionDetector** collisionDetectorGpu, int collisionDetectorIndex) {
		int idx = threadIdx.x + blockIdx.x*blockDim.x;
		if (idx < 1) {
			if (collisionDetectorIndex == CollisionDetectorSimple::INDEX) {
				collisionDetectorGpu[0] = new CollisionDetectorSimple();
			} else {
				printf("collisionDetectorGpu could not be initialised\n");
				assert(false);
			}
		} 
	}
#endif 
#if defined(USE_GPU) 
	__global__
	void setCollisionResolver(CollisionResolver** collisionResolverGpu, int collisionResolverIndex) {
		int idx = threadIdx.x + blockIdx.x*blockDim.x;
		if (idx < 1) {
			if (collisionResolverIndex == CollisionResolverCoalesce::INDEX) {
				collisionResolverGpu[0] = new CollisionResolverCoalesce();
			} else {
				printf("collisionResolverGpu could not be initialised\n");
				assert(false);
			}
		} 
	} 
#endif 

GpuCollision::GpuCollision(std::shared_ptr<CollisionDetector> collisionDetector, std::shared_ptr<CollisionResolver> collisionResolver) : 
	GpuLaw("Collision") {
	cudaWithError->malloc((void**)&collisionDetectorGpu, sizeof(*collisionDetector));
	cudaWithError->malloc((void**)&collisionResolverGpu, sizeof(*collisionResolver));
	#if defined(USE_GPU) 
		cudaWithError->runKernel("setCollisionDetector", [&](unsigned int kernelSize) {
			setCollisionDetector <<<1, 1>>> (collisionDetectorGpu, collisionDetector->getIndex());
			setCollisionResolver <<<1, 1>>> (collisionResolverGpu, collisionResolver->getIndex());
		});
	#endif 
}

GpuCollision::~GpuCollision() {
	cudaWithError->free(collisionDetectorGpu);
	cudaWithError->free(collisionResolverGpu);
}

#if defined(USE_GPU) 
	__global__
	void getCollidedParticles(
		Particle** particles, 
		unsigned long long betweenParticlesOffset, 
		int* collisionMarks, 
		unsigned long long* collisionMarksIndex, 
		unsigned long long maxIntsAllocatable, 
		bool* particlesCollided, 
		CollisionDetector** collisionDetectorGpu, 
		unsigned long long n,
		const long long maxCollisionMarksIndex
	) {
		unsigned long long idx = threadIdx.x + (unsigned long long)blockIdx.x*blockDim.x;
		if (idx < n) { 
			getCollidedParticlesHelper(
				idx + betweenParticlesOffset, 
				particles, 
				collisionMarks, 
				collisionMarksIndex, 
				maxIntsAllocatable, 
				particlesCollided, 
				collisionDetectorGpu,
				maxCollisionMarksIndex
			);
		} 
	}
#endif 

#if defined(USE_GPU) 
	__global__
	void resolveCollidedParticles(
		Particle** particles, 
		int particlesOffset, 
		int* collisionMarks,  
		unsigned long long* collisionMarksIndex, 
		unsigned long long maxIntsAllocatable, 
		bool* particlesCollided, 
		CollisionResolver** collisionResolverGpu,
		int thisParticleCount, 
		int particleCount,		
		unsigned long long betweenParticlesOffset,
		unsigned long long thisBetweenParticleCount,
		const long long maxCollisionMarksIndex,
		bool* limitedReached
	) {
		int idx = threadIdx.x + blockIdx.x*blockDim.x;
		if (idx < thisParticleCount) { 
			resolveCollidedParticlesHelper(
				idx + particlesOffset,
				particles, 
				collisionMarks, 
				collisionMarksIndex, 
				maxIntsAllocatable, 
				particlesCollided, 
				collisionResolverGpu, 
				particleCount,
				betweenParticlesOffset,
				thisBetweenParticleCount,
				maxCollisionMarksIndex,
				limitedReached
			);
		} 
	}
#endif 

void GpuCollision::run(Particle** particles, int particleCount) {
	#if defined(USE_GPU) 
		unsigned long long betweenParticlesPairsCount = ((unsigned long long)particleCount-1)*particleCount;
		unsigned long long betweenParticlesCount = betweenParticlesPairsCount/2;

		unsigned long long* collisionMarksIndex = NULL;
		cudaWithError->malloc((void**)&collisionMarksIndex, sizeof(unsigned long long));

		bool* limitReached = NULL;
		cudaWithError->malloc((void**)&limitReached, sizeof(bool));
		
		bool* particlesCollided = NULL;
		cudaWithError->malloc((void**)&particlesCollided, particleCount * sizeof(bool));

		const double maxFractionMemoryAllocatable = 0.95;
		const long long freeGpuMemoryStage1 = cudaWithError->getFreeGpuMemory();
		const long long freeGpuMemory = (long long)(freeGpuMemoryStage1 * maxFractionMemoryAllocatable);
		const unsigned long long intSize = sizeof(int);
		const long long maxIntsAllocatableStage1 = freeGpuMemory / intSize;
		const unsigned long long maxIntsAllocatableFactor = 200;
		const long long maxIntsAllocatable = std::min(maxIntsAllocatableStage1, (long long)(betweenParticlesPairsCount * maxIntsAllocatableFactor));
		if (maxIntsAllocatable <= 0) {
			throw std::runtime_error("Ran out of GPU memory");
		}

		int* collisionMarks = NULL;
		cudaWithError->malloc((void**)&collisionMarks, maxIntsAllocatable * sizeof(int));

		const unsigned long long maxThreads = cudaWithError->getMaxThreads();
		const unsigned long long maxBetweenParticlesPerGetOverMaxThreads = 5;
		const unsigned long long maxBetweenParticlesPerGet = maxThreads * maxBetweenParticlesPerGetOverMaxThreads;
		const unsigned long long maxParticlesPerResolveMaxThreads = 5;
		const unsigned int maxParticlesPerResolve = (unsigned int)(maxThreads * maxParticlesPerResolveMaxThreads);
		unsigned long long collisionMarksIndexCpu = 0;
		unsigned long long maxCollisionMarksIndex = 2000;
		const unsigned long long minMaxCollisionMarksIndex = 5;
		const unsigned int maxLoops = 20000;
		unsigned int indexLoops = 0;
		bool limitReachedCpu = false;
		// std::cout << std::endl << "maxThreads: " << maxThreads << std::endl;
		do {
			limitReachedCpu = false;
			// std::cout << std::endl << "indexLoops: " << indexLoops << std::endl;
			if (++indexLoops > maxLoops) {
				std::cout << "Max Loops in GpuCollision reached" << std::endl;
				throw std::runtime_error("Max Loops in GpuCollision reached");
			}
			collisionMarksIndexCpu = 0;
			#if defined(USE_GPU)			
				cudaWithError->memcpy(collisionMarksIndex, &collisionMarksIndexCpu, sizeof(collisionMarksIndexCpu), cudaMemcpyHostToDevice);
			#endif
			limitReachedCpu = false;
			cudaWithError->memcpy(limitReached, &limitReachedCpu, sizeof(limitReachedCpu), cudaMemcpyHostToDevice);
			bool particlesCollidedDefault = false;
			#if defined(USE_GPU)
				for(int particleIndex = 0; particleIndex < particleCount; ++particleIndex) {
					cudaWithError->memcpy(&(particlesCollided[particleIndex]), &particlesCollidedDefault, sizeof(bool), cudaMemcpyHostToDevice);
				}
			#endif
			for(unsigned long long betweenParticlesOffset = 0; betweenParticlesOffset < betweenParticlesCount; betweenParticlesOffset += maxBetweenParticlesPerGet) {
				const unsigned long long thisBetweenParticlesCount = std::min(maxBetweenParticlesPerGet, betweenParticlesCount - betweenParticlesOffset);
				#if defined(USE_GPU) 
					cudaWithError->runKernel("getCollidedParticles", [&](unsigned int kernelSize) {
						getCollidedParticles <<<1 + thisBetweenParticlesCount/kernelSize, kernelSize>>> (
							particles, 
							betweenParticlesOffset, 
							collisionMarks, 
							collisionMarksIndex,
							maxIntsAllocatable,
							particlesCollided, 
							collisionDetectorGpu, 
							thisBetweenParticlesCount,
							maxCollisionMarksIndex
						);
					});
				#endif
			}
			cudaWithError->deviceSynchronize("getCollidedParticles");
			for(int particlesOffset = 0; particlesOffset < particleCount; particlesOffset += maxParticlesPerResolve) {
				const int thisParticleCount = std::min(
					maxParticlesPerResolve, 
					(unsigned int)(particleCount - particlesOffset)
				);
				#if defined(USE_GPU)			
					cudaWithError->memcpy(&collisionMarksIndexCpu, collisionMarksIndex, sizeof(collisionMarksIndexCpu), cudaMemcpyDeviceToHost);
				#endif
				collisionMarksIndexCpu = std::min(collisionMarksIndexCpu, maxCollisionMarksIndex);
				#if defined(USE_GPU)			
					cudaWithError->memcpy(collisionMarksIndex, &collisionMarksIndexCpu, sizeof(collisionMarksIndexCpu), cudaMemcpyHostToDevice);
				#endif
				const unsigned int maxBetweenParticlesPerResolve = 10;
				for (unsigned long long betweenParticlesOffset = 0; betweenParticlesOffset < collisionMarksIndexCpu; betweenParticlesOffset += maxBetweenParticlesPerResolve) {
					const unsigned long long thisBetweenParticleCount = (unsigned long long)std::min(
						maxBetweenParticlesPerResolve, 
						(unsigned int)(collisionMarksIndexCpu - betweenParticlesOffset)
					);
					#if defined(USE_GPU)
						cudaWithError->runKernel("resolveCollidedParticles", [&](unsigned int kernelSize) {
							resolveCollidedParticles <<<1 + thisParticleCount/kernelSize, kernelSize>>> (
								particles, 
								particlesOffset,
								collisionMarks, 
								collisionMarksIndex, 
								maxIntsAllocatable,
								particlesCollided, 
								collisionResolverGpu, 
								thisParticleCount, 
								particleCount,
								betweenParticlesOffset,
								thisBetweenParticleCount,
								maxCollisionMarksIndex,
								limitReached
							);
						});
					#endif
				}
			}
			cudaWithError->deviceSynchronize("resolveCollidedParticles");
			// if max loop limited exceeded then reduce minMaxCollisionMarksIndex
			cudaWithError->memcpy(&limitReachedCpu, limitReached, sizeof(limitReachedCpu), cudaMemcpyDeviceToHost);
			if (limitReachedCpu) {
				maxCollisionMarksIndex /= 2;
				// std::cout << std::endl << "maxCollisionMarksIndex reduced" << std::endl;
				if (maxCollisionMarksIndex < minMaxCollisionMarksIndex) {
					std::cout << std::endl << "maxCollisionMarksIndex < minMaxCollisionMarksIndex" << std::endl;
					// throw err;
				}
			}
			// std::cout << std::endl << "collisionMarksIndexCpu: " << collisionMarksIndexCpu << std::endl;
		} while (
			limitReachedCpu ||
			collisionMarksIndexCpu >= maxIntsAllocatable - 1 ||
			collisionMarksIndexCpu >= maxCollisionMarksIndex - 1
		);

		cudaWithError->free(collisionMarks);
		cudaWithError->free(collisionMarksIndex);
		cudaWithError->free(particlesCollided);
	#endif 
}
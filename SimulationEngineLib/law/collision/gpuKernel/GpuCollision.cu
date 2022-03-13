#include "law/collision/gpuKernel/GpuCollision.cuh"
#include "law/collision/helper/GpuCollisionHelper.cuh"
#include "particle/ParticleSimple.h"
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "util/MatrixMaths.cuh"

#include <assert.h>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <typeinfo>

//Cuda doesn't recognise virtual functions of classes initialised on the CPU, so we have to initialise them here
__global__ 
void setCollisionDetector(CollisionDetector** collisionDetectorGpu, int collisionDetectorIndex) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < 1) {
		if(collisionDetectorIndex == CollisionDetectorSimple::INDEX) {
			collisionDetectorGpu[0] = new CollisionDetectorSimple();
		} else {
			printf("collisionDetectorGpu could not be initialised\n");
			assert(false);
		}
	} 
}
__global__ 
void setCollisionResolver(CollisionResolver** collisionResolverGpu, int collisionResolverIndex) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < 1) {
		if(collisionResolverIndex == CollisionResolverCoalesce::INDEX) {
			collisionResolverGpu[0] = new CollisionResolverCoalesce();
		} else {
			printf("collisionResolverGpu could not be initialised\n");
			assert(false);
		}
	} 
} 

GpuCollision::GpuCollision(std::shared_ptr<CollisionDetector> collisionDetector, std::shared_ptr<CollisionResolver> collisionResolver) : 
	GpuLaw("Collision") {
	cudaWithError->malloc((void**)&collisionDetectorGpu, sizeof(*collisionDetector));
	cudaWithError->malloc((void**)&collisionResolverGpu, sizeof(*collisionResolver));
	setCollisionDetector <<<1, 1>>> (collisionDetectorGpu, collisionDetector->getIndex());
	setCollisionResolver <<<1, 1>>> (collisionResolverGpu, collisionResolver->getIndex());
	cudaWithError->peekAtLastError("setCollisionDetector");
}

GpuCollision::~GpuCollision() {
	cudaWithError->free(collisionDetectorGpu);
	cudaWithError->free(collisionResolverGpu);
}

__global__ 
void getCollidedParticles(Particle** particles, unsigned long long betweenParticlesOffset, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionDetector** collisionDetectorGpu, unsigned long long n) {
	unsigned long long idx = threadIdx.x + (unsigned long long)blockIdx.x*blockDim.x;
	if(idx < n) { 
		getCollidedParticlesHelper(idx + betweenParticlesOffset, particles, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionDetectorGpu);
	} 
}

__global__ 
void resolveCollidedParticles(Particle** particles, int particlesOffset, int* collisionMarks,  unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionResolver** collisionResolverGpu, int thisParticleCount, int particleCount) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < thisParticleCount) { 
		resolveCollidedParticlesHelper(idx + particlesOffset, particles, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionResolverGpu, particleCount);
	} 
}

void GpuCollision::run(Particle** particles, int particleCount) {
	unsigned long long betweenParticlesPairsCount = ((unsigned long long)particleCount-1)*particleCount;
	unsigned long long betweenParticlesCount = betweenParticlesPairsCount/2;

	long long freeGpuMemory = cudaWithError->getFreeGpuMemory();
	long long particlesCollidedSize = particleCount * sizeof(bool);
	long long maxIntsAllocatableStage1 = (freeGpuMemory - particlesCollidedSize - (long long)sizeof(unsigned long long)) / (long long)sizeof(int);
	unsigned long long maxIntsAllocatableFactor = 200;
	long long maxIntsAllocatable = std::min(maxIntsAllocatableStage1, (long long)(betweenParticlesPairsCount * maxIntsAllocatableFactor));
	if(maxIntsAllocatable <= 0) {
		throw std::runtime_error("Ran out of GPU memory");
	}
	int* collisionMarks = NULL;
	cudaWithError->malloc((void**)&collisionMarks, maxIntsAllocatable * sizeof(int));

	unsigned long long* collisionMarksIndex = NULL;
	cudaWithError->malloc((void**)&collisionMarksIndex, sizeof(unsigned long long));
	
	bool* particlesCollided = NULL;
	cudaWithError->malloc((void**)&particlesCollided, particleCount * sizeof(bool));

	const unsigned long long maxThreads = cudaWithError->getMaxThreads();
	const unsigned long long maxBetweenParticlesPerGetOverMaxThreads = 37;
	const unsigned long long maxBetweenParticlesPerGet = maxThreads * maxBetweenParticlesPerGetOverMaxThreads;
	const unsigned long long maxParticlesPerResolveOverMaxThreads = 37;
	const unsigned int maxParticlesPerResolve = (unsigned int)(maxThreads * maxBetweenParticlesPerGetOverMaxThreads);
	unsigned long long collisionMarksIndexCpu = 0;
	const unsigned int maxLoops = 20;
	unsigned int indexLoops = 0;
	do {
		if(++indexLoops > maxLoops) {
			std::cout << "Max Loops in GpuCollision reached" << std::endl;
			throw std::runtime_error("Max Loops in GpuCollision reached");
		}
		collisionMarksIndexCpu = 0;
		cudaWithError->memcpy(collisionMarksIndex, &collisionMarksIndexCpu, sizeof(collisionMarksIndexCpu), cudaMemcpyHostToDevice);
		bool particlesCollidedDefault = false;
		for(int particleIndex = 0; particleIndex < particleCount; ++particleIndex) {
			cudaWithError->memcpy(&(particlesCollided[particleIndex]), &particlesCollidedDefault, sizeof(bool), cudaMemcpyHostToDevice);
		}

		for(unsigned long long betweenParticlesOffset = 0; betweenParticlesOffset < betweenParticlesCount; betweenParticlesOffset += maxBetweenParticlesPerGet) {
			const unsigned long long thisBetweenParticlesCount = std::min(maxBetweenParticlesPerGet, betweenParticlesCount - betweenParticlesOffset);
			getCollidedParticles <<<1 + thisBetweenParticlesCount/256, 256>>> (particles, betweenParticlesOffset, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionDetectorGpu, thisBetweenParticlesCount);
			cudaWithError->peekAtLastError("getCollidedParticles");
		}
		cudaWithError->deviceSynchronize("getCollidedParticles");

		for(int particlesOffset = 0; particlesOffset < particleCount; particlesOffset += maxParticlesPerResolve) {
			const int thisParticleCount = std::min(maxParticlesPerResolve, (unsigned int)(particleCount - particlesOffset));
			resolveCollidedParticles <<<1 + thisParticleCount/256, 256>>> (particles, particlesOffset, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionResolverGpu, thisParticleCount, particleCount);
			cudaWithError->peekAtLastError("resolveCollidedParticles");
		}
		cudaWithError->deviceSynchronize("resolveCollidedParticles");
		cudaWithError->memcpy(&collisionMarksIndexCpu, collisionMarksIndex, sizeof(collisionMarksIndexCpu), cudaMemcpyDeviceToHost);
	} while(collisionMarksIndexCpu >= maxIntsAllocatable - 1);

	cudaWithError->free(collisionMarks);
	cudaWithError->free(collisionMarksIndex);
	cudaWithError->free(particlesCollided);
}
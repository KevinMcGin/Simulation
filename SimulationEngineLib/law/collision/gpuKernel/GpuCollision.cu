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

GpuCollision::GpuCollision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver) : GpuLaw("Collision") {
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
void getCollidedParticles(Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionDetector** collisionDetectorGpu, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		getCollidedParticlesHelper(idx, particles, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionDetectorGpu);
	} 
}

__global__ 
void resolveCollidedParticles(Particle** particles, int* collisionMarks,  unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionResolver** collisionResolverGpu, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		resolveCollidedParticlesHelper(idx, particles, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionResolverGpu, n);
	} 
}

void GpuCollision::run(Particle** particles, int particleCount) {
	// get particles that collided
	unsigned long long betweenParticlesCount = ((unsigned long long)particleCount-1)*particleCount/2;

	unsigned long long freeGpuMemory = cudaWithError->getFreeGpuMemory();
	unsigned long long particlesCollidedSize = particleCount * sizeof(bool);
	unsigned long long maxIntsAllocatableStage1 = (freeGpuMemory - particlesCollidedSize - sizeof(unsigned long long)) / sizeof(int);
	unsigned long long maxIntsAllocatable = std::min(maxIntsAllocatableStage1, betweenParticlesCount * 2 * 2000);
	// cout << maxIntsAllocatable << endl;
	int* collisionMarks = NULL;
	cudaWithError->malloc((void**)&collisionMarks, maxIntsAllocatable * sizeof(int));

	unsigned long long* collisionMarksIndex = NULL;
	cudaWithError->malloc((void**)&collisionMarksIndex, sizeof(unsigned long long));
	unsigned long long collisionMarksIndexDefault = 0;
	cudaWithError->memcpy(collisionMarksIndex, &collisionMarksIndexDefault, sizeof(unsigned long long), cudaMemcpyHostToDevice);
	
	bool* particlesCollided = NULL;
	bool particlesCollidedDefault = false;
	cudaWithError->malloc((void**)&particlesCollided, particleCount * sizeof(bool));
	for(int i = 0; i < particleCount; ++i) {
		cudaWithError->memcpy(&(particlesCollided[i]), &particlesCollidedDefault, sizeof(bool), cudaMemcpyHostToDevice);
	}

	getCollidedParticles <<<1 + betweenParticlesCount/256, 256>>> (particles, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionDetectorGpu, betweenParticlesCount);
	cudaWithError->peekAtLastError("getCollidedParticles");

	//TODO remove deviceSynchronize
	cudaWithError->deviceSynchronize("get");

	// merge sets of particles that collided and resolve
	resolveCollidedParticles <<<1 + particleCount/256, 256>>> (particles, collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, collisionResolverGpu, particleCount);
	cudaWithError->peekAtLastError("resolveCollidedParticles");

	//TODO remove deviceSynchronize
	cudaWithError->deviceSynchronize("resolved");
	cudaWithError->free(collisionMarks);
	cudaWithError->free(collisionMarksIndex);
	cudaWithError->free(particlesCollided);
}
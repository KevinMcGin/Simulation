#include "GpuCollision.cuh"
#include "GpuCollisionHelper.cuh"
#include "ParticleSimple.h"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "MatrixMaths.cuh"

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
void getCollidedParticles(Particle** particles, bool* collisionMarks, CollisionDetector** collisionDetectorGpu, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		getCollidedParticlesHelper(idx, particles, collisionMarks, collisionDetectorGpu);
	} 
}

__global__ 
void resolveCollidedParticles(Particle** particles, bool* collisionMarks, CollisionResolver** collisionResolverGpu, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		resolveCollidedParticlesHelper(idx, particles, collisionMarks, collisionResolverGpu, n);
	} 
}

void GpuCollision::run(Particle** td_par, int particleCount) {
	// get particles that collided
	int betweenParticlesCount = (particleCount-1)*particleCount/2;
	bool* collisionMarks = NULL;
	cudaWithError->malloc((void**)&collisionMarks, betweenParticlesCount*sizeof(bool));
	getCollidedParticles <<<1 + betweenParticlesCount/256, 256>>> (td_par, collisionMarks, collisionDetectorGpu, betweenParticlesCount);
	cudaWithError->peekAtLastError("getCollidedParticles");

	// merge sets of particles that collided and resolve
	resolveCollidedParticles <<<1 + particleCount/256, 256>>> (td_par, collisionMarks, collisionResolverGpu, particleCount);
	cudaWithError->peekAtLastError("resolveCollidedParticles");

	cudaWithError->free(collisionMarks);
}
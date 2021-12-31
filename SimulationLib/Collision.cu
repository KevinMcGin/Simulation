#include "Collision.cuh"
#include "ParticleSimple.h"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"
#include "MatrixMaths.cuh"

#include <assert.h>
#include <map>
#include <algorithm>
#include <iterator>
#include <set>
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

Collision::Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool use_gpu): Law("Collision"),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver),
	use_gpu(use_gpu) {
	if(use_gpu) {
		cudaWithError->malloc((void**)&collisionDetectorGpu, sizeof(*collisionDetector));
		cudaWithError->malloc((void**)&collisionResolverGpu, sizeof(*collisionResolver));
		setCollisionDetector <<<1, 1>>> (collisionDetectorGpu, collisionDetector->getIndex());
		setCollisionResolver <<<1, 1>>> (collisionResolverGpu, collisionResolver->getIndex());
		cudaWithError->peekAtLastError("setCollisionDetector");
	}
}

Collision::~Collision() {
	if(use_gpu) {
		cudaWithError->free(collisionDetectorGpu);
		cudaWithError->free(collisionResolverGpu);
	}
}

__global__ 
void getCollidedParticles(Particle** particles, bool* collisionMarks, CollisionDetector** collisionDetectorGpu, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		int x, y;
		MatrixMaths::getLowerTriangularCoordinates(idx, &x, &y);
		auto p1 = particles[x];
		auto p2 = particles[y];
		if (collisionDetectorGpu[0]->isCollision(p1, p2)) {
			collisionMarks[idx] = true;
		} else {
			collisionMarks[idx] = false;			
		}
	} 
}

enum MergeStatus { LOWER_COLLISION_FOUND, COLLISION_FOUND, NO_COLLISION_FOUND };

__device__ MergeStatus mergeCollisionsRows(bool* collisionMarks, int idx, int row, int n, bool firstRun = false);
__device__ MergeStatus mergeCollisionsColumns(bool* collisionMarks, int idx, int row, int n);

__device__ MergeStatus mergeCollisionsRows(bool* collisionMarks, int idx, int row, int n, bool firstRun) {
	bool collisionsToResolve = false;
	MergeStatus mergeStatus = mergeCollisionsColumns(collisionMarks, idx, row, n);
	switch(mergeStatus) {
		case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
		case COLLISION_FOUND: collisionsToResolve = true; break;
		case NO_COLLISION_FOUND: break;
	}
	for(int i = 0; i < row; i++) {
		int collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, row);
		if(collisionMarks[collisionMarksIndex]) {
			int correspondingCollisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
			if(firstRun || !collisionMarks[correspondingCollisionMarksIndex]) {
				collisionMarks[correspondingCollisionMarksIndex] = true;
				collisionsToResolve = true;
				mergeStatus = mergeCollisionsRows(collisionMarks, idx, i, n);
				switch(mergeStatus) {
					case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
				}
			}
		}
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__ MergeStatus mergeCollisionsColumns(bool* collisionMarks, int idx, int row, int n) {
	bool collisionsToResolve = false;
	for(int i = row + 1; i < n; i++) {
		int collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(row, i);
		if(collisionMarks[collisionMarksIndex]) {
			if(i > idx) {
				return LOWER_COLLISION_FOUND;
			} else if(i < idx) {
				int correspondingCollisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
				if(!collisionMarks[correspondingCollisionMarksIndex]) {
					collisionMarks[correspondingCollisionMarksIndex] = true;
					collisionsToResolve = true;
					MergeStatus mergeStatus = mergeCollisionsRows(collisionMarks, idx, i, n);
					switch(mergeStatus) {
						case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
					}
				}
			}
		}
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__global__ 
void resolveCollidedParticles(Particle** particles, bool* collisionMarks, CollisionResolver** collisionResolverGpu, int n) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		auto collisionsToResolve = mergeCollisionsRows(collisionMarks, idx, idx, n, true) == COLLISION_FOUND; 
		if(collisionsToResolve) {
			auto p1 = particles[idx];
			for(int i = 0; i < idx; i++) {
				int collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
				if (collisionMarks[collisionMarksIndex]) {
					auto p2 = particles[i];
					collisionResolverGpu[0]->resolve(p1, p2);
				}
			}
		}
		// delete collisionResolver;
	} 
}

void Collision::cpuRun(vector<Particle*>& particles) {
	// get particles that collided
	vector<set<Particle*>*> particlesCollidedVector;
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
    	set<Particle*> particlesCollidedSet = {};
		for (auto it2 = it1+1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			if (collisionDetector->isCollision(p1, p2)) {
				particlesCollidedSet.insert(p1);
				particlesCollidedSet.insert(p2);
			}
		}
		if(particlesCollidedSet.size() > 0)
			particlesCollidedVector.push_back(new set<Particle*>(particlesCollidedSet));
	}
	// merge sets of particles that collided
	for (auto it1 = particlesCollidedVector.begin(); it1 != particlesCollidedVector.end(); it1++) {
		auto particlesCollided1 = *it1;
		for (auto it2 = it1+1; it2 < particlesCollidedVector.end(); it2++) {
			auto particlesCollided2 = *it2;
			if ([&]() {
				for(auto p: *particlesCollided2) {
					if(particlesCollided1->find(p) != particlesCollided1->end()) {
						return true;
					}
				}
				return false;
			}()) {
				for(auto p: *particlesCollided2) {
					particlesCollided1->insert(p);
				}
				particlesCollided2->clear();
			}
		}
	}
	//resolve particles
	for (auto particlesCollided1: particlesCollidedVector) {
		if(particlesCollided1->size() > 0) {
			auto p1 = *(particlesCollided1->begin());
			particlesCollided1->erase(particlesCollided1->begin());
			for(auto p2: *particlesCollided1) {
				collisionResolver->resolve(p1, p2);
			}
		}
	}
	//erase particles marked for deletion safely
	for (auto it = particles.begin(); it != particles.end();) {
		if((*it)->deleted) {
			delete *it;
			it = particles.erase(it);
		}
		else
			++it;
	}
}

void Collision::gpuRun(Particle** td_par, int particleCount) {
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
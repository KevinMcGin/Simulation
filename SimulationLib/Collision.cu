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

Collision::Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver): Law("Collision"),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver) {
		
}

__global__ 
void getCollidedParticles(Particle** particles, bool* collisionMarks, int n, int collisionDetectorIndex) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		//TODO find soluation to this, creating new class with a pointer is slow on GPU threads
		//Cuda doesn't recognise virtual functions of classes initialised on the CPU, so we have to initialise them here
		// CollisionDetector* collisionDetector;
		// if(collisionDetectorIndex == CollisionDetectorSimple::INDEX) {
		// 	collisionDetector = new CollisionDetectorSimple();
		// } else {
		// 	//printf("CollisionDetector could not be initialised\n");
		// 	assert(false);
		// }
		CollisionDetectorSimple collisionDetector = CollisionDetectorSimple();
		int x, y;
		MatrixMaths::getLowerTriangularCoordinates(idx, &x, &y);
		auto p1 = particles[x];
		auto p2 = particles[y];
		if (collisionDetector.isCollision(p1, p2)) {
			collisionMarks[idx] = true;
		} else {
			collisionMarks[idx] = false;			
		}
		// delete collisionDetector;
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
void resolveCollidedParticles(Particle** particles, bool* collisionMarks, int n, int collisionResolverIndex) {
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < n) { 
		//TODO find soluation to this, creating new class with a pointer is slow on GPU threads
		//Cuda doesn't recognise virtual functions of classes initialised on the CPU, so we have to initialise them here
		// CollisionResolver* collisionResolver;
		// if(collisionResolverIndex == CollisionResolverCoalesce::INDEX) {
		// 	collisionResolver = new CollisionResolverCoalesce();
		// } else {
		// 	//printf("CollisionResolver could not be initialised\n");
		// 	assert(false);
		// }
		CollisionResolverCoalesce collisionResolver = CollisionResolverCoalesce();
		auto collisionsToResolve = mergeCollisionsRows(collisionMarks, idx, idx, n, true) == COLLISION_FOUND; 
		if(collisionsToResolve) {
			auto p1 = particles[idx];
			for(int i = 0; i < idx; i++) {
				int collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
				if (collisionMarks[collisionMarksIndex]) {
					auto p2 = particles[i];
					collisionResolver.resolve(p1, p2);
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
	getCollidedParticles <<<1 + betweenParticlesCount/256, 256>>> (td_par, collisionMarks, betweenParticlesCount, collisionDetector->getIndex());
	cudaWithError->peekAtLastError("getCollidedParticles");

	// merge sets of particles that collided and resolve
	resolveCollidedParticles <<<1 + particleCount/256, 256>>> (td_par, collisionMarks, particleCount, collisionResolver->getIndex());
	cudaWithError->peekAtLastError("resolveCollidedParticles");

	cudaWithError->free(collisionMarks);
}
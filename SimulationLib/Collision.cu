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
		//printf("getCollidedParticles\n");
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
		//printf("Got particles\n");
		if (collisionDetector.isCollision(p1, p2)) {
			//printf("Collision. %d: %d, %d\n", idx, x, y);
			collisionMarks[idx] = true;
		} else {
			//printf("No collision\n");
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
		int collisionMarksIndex = MatrixMaths::getLowerTriangularIndx(i, row);
		if(collisionMarks[collisionMarksIndex]) {
			int correspondingCollisionMarksIndex = MatrixMaths::getLowerTriangularIndx(i, idx);
			if(firstRun || !collisionMarks[correspondingCollisionMarksIndex]) {
				//printf("ROWS for %d. %d: %d, %d\n", idx, collisionMarksIndex, row, i);
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
		int collisionMarksIndex = MatrixMaths::getLowerTriangularIndx(row, i);
		if(collisionMarks[collisionMarksIndex]) {
			if(i > idx) {
				//printf("LOWER_COLLISION_FOUND for %d. %d: %d, %d\n", idx, collisionMarksIndex, row, i);
				return LOWER_COLLISION_FOUND;
			} else if(i < idx) {
				int correspondingCollisionMarksIndex = MatrixMaths::getLowerTriangularIndx(i, idx);
				if(!collisionMarks[correspondingCollisionMarksIndex]) {
					//printf("COLS for %d, %d. %d, %d: %d, %d\n", idx, row, collisionMarksIndex, correspondingCollisionMarksIndex, row, i);
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
		//printf("resolveCollidedParticles\n");
		//Cuda doesn't recognise virtual functions of classes initialised on the CPU, so we have to initialise them here
		// CollisionResolver* collisionResolver;
		// if(collisionResolverIndex == CollisionResolverCoalesce::INDEX) {
		// 	collisionResolver = new CollisionResolverCoalesce();
		// } else {
		// 	//printf("CollisionResolver could not be initialised\n");
		// 	assert(false);
		// }
		CollisionResolverCoalesce collisionResolver = CollisionResolverCoalesce();
		auto mergeStatus = mergeCollisionsRows(collisionMarks, idx, idx, n, true);
		switch(mergeStatus) {
			case LOWER_COLLISION_FOUND  ://printf("%d: LOWER_COLLISION_FOUND\n", idx);   break;
			case COLLISION_FOUND: //printf("%d: COLLISION_FOUND\n", idx); break;
			case NO_COLLISION_FOUND : //printf("%d: NO_COLLISION_FOUND\n", idx);  break;
		}
		bool collisionsToResolve = mergeStatus == COLLISION_FOUND;
		if(collisionsToResolve) {
			auto p1 = particles[idx];
			for(int i = 0; i < idx; i++) {
				int collisionMarksIndex = i + (idx-1)*idx/2;
				if (collisionMarks[collisionMarksIndex]) {
					//printf("Resolving collision: %d, %d\n", idx, i);
					auto p2 = particles[i];
					collisionResolver.resolve(p1, p2);
				}
			}
		}
		// delete collisionResolver;
	} 
}

void Collision::cpuRun(vector<Particle*>& particles)
{
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


void Collision::gpuRun(vector<Particle*>& particles) {
	cudaWithError->setDevice(0);
	int particleCount = (int)particles.size();

	//Instantiate object on the CPU
	auto particlesArray = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i)
		particlesArray[i] = particles[i];

	//Copy dynamically allocated child objects to GPU
	Particle ** d_par;
	d_par = new Particle*[particleCount];
	for(int i = 0; i < particleCount; ++i) {
		cudaWithError->malloc((void**)&d_par[i],sizeof(ParticleSimple));
		cudaWithError->memcpy(d_par[i], particlesArray[i], sizeof(ParticleSimple), cudaMemcpyHostToDevice);
	}

	//Copy the d_par array itself to the device
	Particle** td_par;
	cudaWithError->malloc((void**)&td_par, particleCount * sizeof(Particle *));
	cudaWithError->memcpy(td_par, d_par, particleCount * sizeof(Particle *), cudaMemcpyHostToDevice);

	// get particles that collided
	int betweenParticlesCount = (particleCount-1)*particleCount/2;
	bool* collisionMarks = NULL;
	cudaWithError->malloc((void**)&collisionMarks, betweenParticlesCount*sizeof(bool));
	getCollidedParticles <<<1 + betweenParticlesCount/256, 256>>> (td_par, collisionMarks, betweenParticlesCount, collisionDetector->getIndex());
	cudaWithError->deviceSynchronize("getCollidedParticles");

	// merge sets of particles that collided and resolve
	resolveCollidedParticles <<<1 + particleCount/256, 256>>> (td_par, collisionMarks, particleCount, collisionResolver->getIndex());
	cudaWithError->deviceSynchronize("resolveCollidedParticles");

	//copy particles back to cpu
	for(int i = 0; i < particleCount; i++) {
		cudaWithError->memcpy(particlesArray[i],d_par[i],sizeof(ParticleSimple),cudaMemcpyDeviceToHost);
		cudaWithError->free(d_par[i]);
		particles[i] = particlesArray[i];
	}

	//TODO: do this on gpu
	//erase particles marked for deletion safely
	for (auto it = particles.begin(); it != particles.end();) {
		if((*it)->deleted) {
			delete *it;
			it = particles.erase(it);
		}
		else
			++it;
	}

	cudaWithError->free(td_par);
	cudaWithError->free(collisionMarks);
	delete particlesArray;
	delete d_par;
	
	// cout << "Got to the end" << endl;
}
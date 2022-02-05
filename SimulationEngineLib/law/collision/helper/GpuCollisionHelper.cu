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

const int MAX_MERGE_COLLISION_RUNS = 5;

__device__ MergeStatus mergeCollisionsRows(int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, int idx, int row, int n, int runCount = 0);
__device__ MergeStatus mergeCollisionsColumns(int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable,  bool* particlesCollided, int idx, int row, int n, int runCount = 0);

__device__ int getNextParticleCollidedByIndex(int* collisionMarks, unsigned long long collisionMarksIndex, unsigned long long* thisCollisionMarksIndex, int particleIndex, bool index1 = true) {
	unsigned long long indexOffset1 = index1 ? 0 : 1;
	unsigned long long indexOffset2 = index1 ? 1 : 0;
	unsigned long long thisCollisionMarksIndexActual = *thisCollisionMarksIndex;
	while(thisCollisionMarksIndexActual < collisionMarksIndex) {
		unsigned long long index1Long = thisCollisionMarksIndexActual + indexOffset1;
		unsigned long long index2Long = thisCollisionMarksIndexActual + indexOffset2;
		int thisParticleIndex1 = collisionMarks[index1Long];
		int thisParticleIndex2 = collisionMarks[index2Long];
		// printf("particle indices: %llu: %d, %d\n", thisCollisionMarksIndexActual, thisParticleIndex1, thisParticleIndex2);
		thisCollisionMarksIndexActual += 2;
		// printf("getNextParticleCollidedByIndex: %llu, %llu\n", index1Long, index2Long);
		if(thisParticleIndex1 == particleIndex) {
			// printf("getNextParticleCollidedByIndex: %llu, %llu\n", index1Long, index2Long);
			*thisCollisionMarksIndex = thisCollisionMarksIndexActual;
			return thisParticleIndex2;
		}
		
	}
	*thisCollisionMarksIndex = thisCollisionMarksIndexActual;
	return -1;
}

__device__ bool getParticlesCollidedByIndex(int* collisionMarks, unsigned long long collisionMarksIndex, int particleIndex1, int particleIndex2) {
	unsigned long long thisCollisionMarksIndexActual = 0;
	int thisParticleIndex2 = getNextParticleCollidedByIndex(collisionMarks, collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex1);
	while(thisParticleIndex2 >= 0) {
		//printf("thisParticleIndex2: %d, %d\n", particleIndex1, thisParticleIndex2);
		if(thisParticleIndex2 == particleIndex2) {
			return true;
		}
		thisParticleIndex2 = getNextParticleCollidedByIndex(collisionMarks, collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex1);
	}
	return false;
}

__device__ void markCollision(int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, int particleIndex1, int particleIndex2) {
	unsigned long long i = atomicAdd(collisionMarksIndex, 2);
	// printf("maxIntsAllocatable: %llu\n", maxIntsAllocatable);
	// printf("Marking collision at: %llu: %d, %d\n", i, particleIndex1, particleIndex2);
	if(i + 1 >= maxIntsAllocatable - 1) {
		printf("GpuCollisionHelper: collisionMarks overflow\n");
		return;
	}
	particlesCollided[particleIndex1] = true;
	collisionMarks[i] = particleIndex1;
	collisionMarks[i + 1] = particleIndex2;
}

__device__
MergeStatus mergeCollisionsRows(int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, int idx, int row, int n, int runCount) {  
	// printf("rows: idx: %d row: %d\n", idx, row);
	if(!particlesCollided[row] || (runCount > 0 && idx == row) || runCount >= MAX_MERGE_COLLISION_RUNS) {
		return NO_COLLISION_FOUND;
	}
	bool collisionsToResolve = false;
	MergeStatus mergeStatus = mergeCollisionsColumns(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, idx, row, n, runCount + 1);
	//printf("row: %d, mergeStatus: %d\n", row, mergeStatus);
	switch(mergeStatus) {
		case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
		case COLLISION_FOUND: collisionsToResolve = true; break;
		case NO_COLLISION_FOUND: break;
	}	
	unsigned long long thisCollisionMarksIndexActual = 0;
	int collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, row);
	//printf("collidedParticleIndex: %d\n", collidedParticleIndex);
	while(collidedParticleIndex >= 0) {
		if(runCount == 0 || !getParticlesCollidedByIndex(collisionMarks, *collisionMarksIndex, idx, collidedParticleIndex)) {
			//printf("rows: collidedParticleIndex: %d\n", collidedParticleIndex);
			if(runCount > 0 && idx != collidedParticleIndex) {
				// printf("rows: collisionMarksIndex: %llu\n", *collisionMarksIndex);
				markCollision(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, idx, collidedParticleIndex);
			}
			collisionsToResolve = true;
			mergeStatus = mergeCollisionsRows(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, idx, collidedParticleIndex, n, runCount + 1);
			switch(mergeStatus) {
				case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
			}
		}
		collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, row);
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__ 
MergeStatus mergeCollisionsColumns(int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, int idx, int row, int n, int runCount) {
	if(runCount >= MAX_MERGE_COLLISION_RUNS) {
		return NO_COLLISION_FOUND;
	}
	//printf("cols: idx: %d, row: %d\n", idx, row);
	bool collisionsToResolve = false;
	unsigned long long thisCollisionMarksIndexActual = 0;
	int collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, row, false);
	//printf("cols: idx: %d, row: %d, collidedParticleIndex: %d\n", idx, row, collidedParticleIndex);
	while(collidedParticleIndex >= 0) {
		if(collidedParticleIndex > idx) {
			return LOWER_COLLISION_FOUND;
		} else if(collidedParticleIndex < idx) {
			if(!getParticlesCollidedByIndex(collisionMarks, *collisionMarksIndex, idx, collidedParticleIndex)) {
				//printf("cols: %d, %d\n", idx, collidedParticleIndex);
				//printf("cols: collisionMarksIndex: %llu\n", *collisionMarksIndex);
				// printf("col: Marking collision at: %llu: %d, %d\n", *collisionMarksIndex, idx, collidedParticleIndex);
				markCollision(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, idx, collidedParticleIndex);
				collisionsToResolve = true;
				MergeStatus mergeStatus = mergeCollisionsRows(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, idx, collidedParticleIndex, n, runCount + 1);
				switch(mergeStatus) {
					case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
				}
			}
		}
		collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, row, false);
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__ 
void resolveCollidedParticlesHelper(int idx, Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionResolver** collisionResolverGpu, int n) {
	if(particlesCollided[idx]) {
		auto collisionsToResolve = mergeCollisionsRows(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, idx, idx, n) == COLLISION_FOUND; 
		if(collisionsToResolve) {
			// printf("resolving particle: %d\n", idx);
			auto p1 = particles[idx];
			for(unsigned long long i = 0; i < *collisionMarksIndex; i += 2) {
				//printf("resolveCollidedParticlesHelper: collisionMarksIndex: %llu\n", i);
				if(collisionMarks[i] == idx) {
					int particleCollidedIndex = collisionMarks[i + 1];
					//printf("Resolving: %d - %d\n", idx, particleCollidedIndex);
					auto p2 = particles[particleCollidedIndex];
					(*collisionResolverGpu)->resolve(p1, p2);
				}
			}
		}
	}
}

__device__
void getCollidedParticlesHelper(unsigned long long idx, Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionDetector** collisionDetectorGpu) {
	unsigned long long x, y;
	MatrixMaths::getLowerTriangularCoordinates(idx, &x, &y);
	//TODO find out why out of bounds error is occuring here
	auto p1 = particles[x];
	auto p2 = particles[y];	
	if((*collisionDetectorGpu)->isCollision(p1, p2)) {		
		// //printf("Collision: %llu - %llu\n", x, y);	
		// //printf("Getting collision: %llu \n", *collisionMarksIndex);
		// printf("get: Marking collision at: %llu: %d, %d\n", *collisionMarksIndex, (int)y, (int)x);
		markCollision(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, (int)y, (int)x);
	}
}
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

const int MAX_MERGE_COLLISION_RUNS = 100;

__device__ MergeStatus mergeCollisionsRows(bool* collisionMarks, int idx, int row, int n, int runCount = 0);
__device__ MergeStatus mergeCollisionsColumns(bool* collisionMarks, int idx, int row, int n, int runCount = 0);

__device__
MergeStatus mergeCollisionsRows(bool* collisionMarks, int idx, int row, int n, int runCount) {
	if(runCount > MAX_MERGE_COLLISION_RUNS) {
		return NO_COLLISION_FOUND;
	}
	bool collisionsToResolve = false;
	MergeStatus mergeStatus = mergeCollisionsColumns(collisionMarks, idx, row, n, runCount + 1);
	switch(mergeStatus) {
		case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
		case COLLISION_FOUND: collisionsToResolve = true; break;
		case NO_COLLISION_FOUND: break;
	}
	for(int i = 0; i < row; i++) {
		unsigned long long collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, row);
		if(collisionMarks[collisionMarksIndex]) {
			unsigned long long correspondingCollisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
			if(runCount == 0 || !collisionMarks[correspondingCollisionMarksIndex]) {
				collisionMarks[correspondingCollisionMarksIndex] = true;
				collisionsToResolve = true;
				mergeStatus = mergeCollisionsRows(collisionMarks, idx, i, n, runCount + 1);
				switch(mergeStatus) {
					case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
				}
			}
		}
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__ 
MergeStatus mergeCollisionsColumns(bool* collisionMarks, int idx, int row, int n, int runCount) {
	if(runCount > MAX_MERGE_COLLISION_RUNS) {
		return NO_COLLISION_FOUND;
	}
	bool collisionsToResolve = false;
	for(int i = row + 1; i < n; i++) {
		unsigned long long collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(row, i);
		if(collisionMarks[collisionMarksIndex]) {
			if(i > idx) {
				return LOWER_COLLISION_FOUND;
			} else if(i < idx) {
				unsigned long long correspondingCollisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
				if(!collisionMarks[correspondingCollisionMarksIndex]) {
					collisionMarks[correspondingCollisionMarksIndex] = true;
					collisionsToResolve = true;
					MergeStatus mergeStatus = mergeCollisionsRows(collisionMarks, idx, i, n, runCount + 1);
					switch(mergeStatus) {
						case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
					}
				}
			}
		}
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__ 
void resolveCollidedParticlesHelper(int idx, Particle** particles, bool* collisionMarks, CollisionResolver** collisionResolverGpu, int n) {
	auto collisionsToResolve = mergeCollisionsRows(collisionMarks, idx, idx, n) == COLLISION_FOUND; 
	if(collisionsToResolve) {
		auto p1 = particles[idx];
		for(int i = 0; i < idx; i++) {
			unsigned long long collisionMarksIndex = MatrixMaths::getLowerTriangularIndex(i, idx);
			if (collisionMarks[collisionMarksIndex]) {
				auto p2 = particles[i];
				collisionResolverGpu[0]->resolve(p1, p2);
			}
		}
	}
}


__device__
void getCollidedParticlesHelper(int idx, Particle** particles, bool* collisionMarks, CollisionDetector** collisionDetectorGpu) {
	unsigned long long x, y;
	MatrixMaths::getLowerTriangularCoordinates(idx, &x, &y);
	auto p1 = particles[x];
	auto p2 = particles[y];
	if (collisionDetectorGpu[0]->isCollision(p1, p2)) {
		collisionMarks[idx] = true;
	} else {
		collisionMarks[idx] = false;			
	}
}
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

__device__
MergeStatus mergeCollisionsRows(bool* collisionMarks, int idx, int row, int n, bool firstRun) {
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

__device__ 
MergeStatus mergeCollisionsColumns(bool* collisionMarks, int idx, int row, int n) {
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

__device__ 
void resolveCollidedParticlesHelper(int idx, Particle** particles, bool* collisionMarks, CollisionResolver** collisionResolverGpu, int n) {
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
}


__device__
void getCollidedParticlesHelper(int idx, Particle** particles, bool* collisionMarks, CollisionDetector** collisionDetectorGpu) {
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
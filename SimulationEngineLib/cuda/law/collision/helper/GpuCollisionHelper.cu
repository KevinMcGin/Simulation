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

// Todo: revisit these limits; stop all processes if limit is reached so that maxCollisionMarksIndex can be reduced
const int MAX_MERGE_COLLISION_RUNS = 5;
const int MAX_COLLISIONS_PER_PARTICLE = 5;

__device__
MergeStatus mergeCollisionsRows(
	int* collisionMarks, 
	unsigned long long* collisionMarksIndex, 
	unsigned long long maxIntsAllocatable, 
	bool* particlesCollided, 
	int particleIndex1, 
	int particleIndex2, 
	int particleCount,
	const long long maxCollisionMarksIndex,
	bool* limitReached,
	int runCount = 0
);

__device__
MergeStatus mergeCollisionsColumns(
	int* collisionMarks, 
	unsigned long long* 
	collisionMarksIndex,
	unsigned long long maxIntsAllocatable,  
	bool* particlesCollided, 
	int particleIndex1, 
	int particleIndex2, 
	int particleCount,
	const long long maxCollisionMarksIndex,
	bool* limitReached,
	int runCount = 0
);

__device__
int getNextParticleCollidedByIndex(int* collisionMarks, unsigned long long collisionMarksIndex, unsigned long long* thisCollisionMarksIndex, int particleIndex, bool index1 = true) {
	unsigned long long indexOffset1 = index1 ? 0 : 1;
	unsigned long long indexOffset2 = index1 ? 1 : 0;
	unsigned long long thisCollisionMarksIndexActual = *thisCollisionMarksIndex;
	while(thisCollisionMarksIndexActual < collisionMarksIndex) {
		unsigned long long index1Long = thisCollisionMarksIndexActual + indexOffset1;
		unsigned long long index2Long = thisCollisionMarksIndexActual + indexOffset2;
		int thisParticleIndex1 = collisionMarks[index1Long];
		int thisParticleIndex2 = collisionMarks[index2Long];
		thisCollisionMarksIndexActual += 2;
		if (thisParticleIndex1 == particleIndex) {
			*thisCollisionMarksIndex = thisCollisionMarksIndexActual;
			return thisParticleIndex2;
		}
		
	}
	*thisCollisionMarksIndex = thisCollisionMarksIndexActual;
	return -1;
}

__device__
bool getParticlesCollidedByIndex(int* collisionMarks, unsigned long long collisionMarksIndex, int particleIndex1, int particleIndex2) {
	unsigned long long thisCollisionMarksIndexActual = 0;
	int thisParticleIndex2 = getNextParticleCollidedByIndex(collisionMarks, collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex1);
	while(thisParticleIndex2 >= 0) {
		if (thisParticleIndex2 == particleIndex2) {
			return true;
		}
		thisParticleIndex2 = getNextParticleCollidedByIndex(collisionMarks, collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex1);
	}
	return false;
}

__device__
bool markCollision(int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, int particleIndex1, int particleIndex2) {
	unsigned long long i = atomicAdd(collisionMarksIndex, 2);
	if (i + 1 >= maxIntsAllocatable - 1) {
		return false;
	}
	particlesCollided[particleIndex1] = true;
	collisionMarks[i] = particleIndex1;
	collisionMarks[i + 1] = particleIndex2;
	return true;
}

__device__
MergeStatus mergeCollisionsRows(
	int* collisionMarks, 
	unsigned long long* collisionMarksIndex, 
	unsigned long long maxIntsAllocatable, 
	bool* particlesCollided, 
	int particleIndex1, 
	int particleIndex2, 
	int particleCount,
	const long long maxCollisionMarksIndex, 
	bool* limitReached,
	int runCount
) {
	int collisionsFound = 0;
	if (*limitReached || !particlesCollided[particleIndex2] || (runCount > 0 && particleIndex1 == particleIndex2) || runCount >= MAX_MERGE_COLLISION_RUNS) {
		return NO_COLLISION_FOUND;
	}
	bool collisionsToResolve = false;
	MergeStatus mergeStatus = mergeCollisionsColumns(
		collisionMarks, 
		collisionMarksIndex, 
		maxIntsAllocatable, 
		particlesCollided, 
		particleIndex1, 
		particleIndex2, 
		particleCount,
		maxCollisionMarksIndex, 
		limitReached,
		runCount + 1
	);
	switch(mergeStatus) {
		case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
		case COLLISION_FOUND: collisionsToResolve = true; break;
		case NO_COLLISION_FOUND: break;
	}	
	unsigned long long thisCollisionMarksIndexActual = 0;
	int collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex2);
	while(collidedParticleIndex >= 0) {
		if (runCount == 0 || !getParticlesCollidedByIndex(collisionMarks, *collisionMarksIndex, particleIndex1, collidedParticleIndex)) {
			if (++collisionsFound >= MAX_COLLISIONS_PER_PARTICLE) {
				*limitReached = true;
				return NO_COLLISION_FOUND;
			}
			if (*collisionMarksIndex < maxCollisionMarksIndex && runCount > 0 && particleIndex1 != collidedParticleIndex) {
				bool collisionMarked = markCollision(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, particleIndex1, collidedParticleIndex);
				if (!collisionMarked) {
					return NO_COLLISION_FOUND;
				}
			}
			collisionsToResolve = true;
			mergeStatus = mergeCollisionsRows(
				collisionMarks, 
				collisionMarksIndex,
				maxIntsAllocatable, 
				particlesCollided, 
				particleIndex1, 
				collidedParticleIndex, 
				particleCount, 
				maxCollisionMarksIndex,
				limitReached,
				runCount + 1
			);
			switch(mergeStatus) {
				case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
			}
		}
		collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex2);
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__
MergeStatus mergeCollisionsColumns(
	int* collisionMarks, 
	unsigned long long* collisionMarksIndex, 
	unsigned long long maxIntsAllocatable, 
	bool* particlesCollided, 
	int particleIndex1, 
	int particleIndex2, 
	int particleCount,
	const long long maxCollisionMarksIndex, 
	bool* limitReached,
	int runCount
) {
	int collisionsFound = 0;
	if (*limitReached || runCount >= MAX_MERGE_COLLISION_RUNS) {
		return NO_COLLISION_FOUND;
	}
	bool collisionsToResolve = false;
	unsigned long long thisCollisionMarksIndexActual = 0;
	int collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex2, false);
	while(!*limitReached && collidedParticleIndex >= 0) {
		if (collidedParticleIndex > particleIndex1) {
			return LOWER_COLLISION_FOUND;
		} else if (collidedParticleIndex < particleIndex1) {
			if (!getParticlesCollidedByIndex(collisionMarks, *collisionMarksIndex, particleIndex1, collidedParticleIndex)) {
				if (++collisionsFound >= MAX_COLLISIONS_PER_PARTICLE) {
					return COLLISION_FOUND;
				}
				bool collisionMarked = markCollision(collisionMarks, collisionMarksIndex, maxIntsAllocatable, particlesCollided, particleIndex1, collidedParticleIndex);
				if (!collisionMarked) {
					return NO_COLLISION_FOUND;
				}
				collisionsToResolve = true;
				MergeStatus mergeStatus = mergeCollisionsRows(
					collisionMarks, 
					collisionMarksIndex, 
					maxIntsAllocatable, 
					particlesCollided, 
					particleIndex1, 
					collidedParticleIndex, 
					particleCount, 
					maxCollisionMarksIndex,
					limitReached,
					runCount + 1
				);
				switch(mergeStatus) {
					case LOWER_COLLISION_FOUND: return LOWER_COLLISION_FOUND;
				}
			}
		}
		collidedParticleIndex = getNextParticleCollidedByIndex(collisionMarks, *collisionMarksIndex, &thisCollisionMarksIndexActual, particleIndex2, false);
	}
	return collisionsToResolve ? COLLISION_FOUND : NO_COLLISION_FOUND;
}

__device__
void resolveCollidedParticlesHelper(
	int particleIndex, 
	Particle** particles, 
	int* collisionMarks, 
	unsigned long long* collisionMarksIndex, 
	unsigned long long maxIntsAllocatable, 
	bool* particlesCollided, 
	CollisionResolver** collisionResolverGpu, 
	int particleCount,		
	unsigned long long betweenParticlesOffset,
	unsigned long long thisBetweenParticleCount,
	const long long maxCollisionMarksIndex,	
	bool* limitReached,
	MomentumService** momentumServiceGpu
) {
	if (particlesCollided[particleIndex]) {
		// printf(" collisionMarksIndex '%llu' ", *collisionMarksIndex);
		auto collisionsToResolve = mergeCollisionsRows(
			collisionMarks, 
			collisionMarksIndex, 
			maxIntsAllocatable, 
			particlesCollided, 
			particleIndex, 
			particleIndex,
			particleCount,
			maxCollisionMarksIndex,
			limitReached
		) == COLLISION_FOUND; 
		if (collisionsToResolve) {
			auto p1 = particles[particleIndex];
			for(unsigned long long i = 0; i < thisBetweenParticleCount; i += 2) {
				if (collisionMarks[betweenParticlesOffset + i] == particleIndex) {
					int particleCollidedIndex = collisionMarks[betweenParticlesOffset + i + 1];
					auto p2 = particles[particleCollidedIndex];
					if (p1->particlesExist(p2)) {
						(*collisionResolverGpu)->resolve(p1, p2, *momentumServiceGpu);
					}
				}
			}
		}
	}
}

__device__
void getCollidedParticlesHelper(
	unsigned long long lowerTriangularIndex, 
	Particle** particles, 
	int* collisionMarks, 
	unsigned long long* collisionMarksIndex, 
	unsigned long long maxIntsAllocatable, 
	bool* particlesCollided, 
	CollisionDetector** collisionDetectorGpu,
	const long long maxCollisionMarksIndex
) {
	unsigned long long x, y;
	MatrixMaths::getLowerTriangularCoordinates(lowerTriangularIndex, &x, &y);
	auto p1 = particles[x];
	auto p2 = particles[y];	
	auto actualCollisionMarksIndex = *collisionMarksIndex;
	if (
		actualCollisionMarksIndex < maxCollisionMarksIndex && 
		p1->particlesExist(p2) && 
		(*collisionDetectorGpu)->isCollision(p1, p2)
	) {		
		bool collisionMarked = markCollision(
			collisionMarks, 
			collisionMarksIndex,
			maxIntsAllocatable, 
			particlesCollided, 
			(int)y, 
			(int)x
		);
		// if (!collisionMarked) {
		// 	printf("getCollidedParticlesHelper: collisionMarks overflow\n");
		// }
	}
}
#pragma once
#include "cuda_runtime.h"
#include "particle/Particle.cuh"
#include "law/collision/helper/GpuCollisionHelper.cuh"
#include "law/collision/resolver/CollisionResolver.cuh"
#include "law/collision/detector/CollisionDetector.cuh"

enum MergeStatus { LOWER_COLLISION_FOUND, COLLISION_FOUND, NO_COLLISION_FOUND };

__device__ void resolveCollidedParticlesHelper(int particleIndex, Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionResolver** collisionResolverGpu, int particleCount);
__device__ void getCollidedParticlesHelper(unsigned long long lowerTriangularIndex, Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionDetector** collisionDetectorGpu);
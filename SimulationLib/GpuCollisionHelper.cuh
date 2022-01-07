#pragma once
#include "cuda_runtime.h"
#include "Particle.cuh"
#include "GpuCollisionHelper.cuh"
#include "CollisionResolver.cuh"
#include "CollisionDetector.cuh"

enum MergeStatus { LOWER_COLLISION_FOUND, COLLISION_FOUND, NO_COLLISION_FOUND };

__device__ MergeStatus mergeCollisionsRows(bool* collisionMarks, int idx, int row, int n, bool firstRun = false);
__device__ MergeStatus mergeCollisionsColumns(bool* collisionMarks, int idx, int row, int n);

__device__ void resolveCollidedParticlesHelper(int idx, Particle** particles, bool* collisionMarks, CollisionResolver** collisionResolverGpu, int n);
__device__ void getCollidedParticlesHelper(int idx, Particle** particles, bool* collisionMarks, CollisionDetector** collisionDetectorGpu);
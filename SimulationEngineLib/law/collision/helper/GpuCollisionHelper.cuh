#pragma once
#if defined(USE_GPU)
    #include "cuda_runtime.h"
#endif
#include "particle/Particle.cuh"
#include "law/collision/helper/GpuCollisionHelper.cuh"
#include "law/collision/resolver/CollisionResolver.cuh"
#include "law/collision/detector/CollisionDetector.cuh"

#ifndef MERGE_STATUS
#define MERGE_STATUS
   enum MergeStatus { LOWER_COLLISION_FOUND, COLLISION_FOUND, NO_COLLISION_FOUND };
#endif
 
#if defined(USE_GPU)
   __device__
#endif
void resolveCollidedParticlesHelper(int particleIndex, Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionResolver** collisionResolverGpu, int particleCount);
#if defined(USE_GPU)
   __device__
#endif
void getCollidedParticlesHelper(unsigned long long lowerTriangularIndex, Particle** particles, int* collisionMarks, unsigned long long* collisionMarksIndex, unsigned long long maxIntsAllocatable, bool* particlesCollided, CollisionDetector** collisionDetectorGpu);
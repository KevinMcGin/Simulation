#pragma once
#if defined(USE_GPU)
    #include "cuda_runtime.h"
#endif
#include "shared/particle/Particle.cuh"
#include "cuda/law/collision/helper/GpuCollisionHelper.cuh"
#include "shared/law/collision/resolver/CollisionResolver.cuh"
#include "shared/law/collision/detector/CollisionDetector.cuh"

#ifndef MERGE_STATUS
#define MERGE_STATUS
   enum MergeStatus { LOWER_COLLISION_FOUND, COLLISION_FOUND, NO_COLLISION_FOUND };
#endif
 
#if defined(USE_GPU)
   __device__
#endif
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
	bool* limitReached
);
#if defined(USE_GPU)
   __device__
#endif
void getCollidedParticlesHelper(
   unsigned long long lowerTriangularIndex, 
   Particle** particles, 
   int* collisionMarks, 
   unsigned long long* collisionMarksIndex, 
   unsigned long long maxIntsAllocatable, 
   bool* particlesCollided, CollisionDetector** collisionDetectorGpu,
   const long long maxCollisionMarksIndex
);
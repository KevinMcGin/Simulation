#include "law/collision/Collision.h"
#include "law/collision/CpuCollision.h"
#include "law/collision/gpuKernel/GpuCollision.cuh"

Collision::Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool useGpu) : 
    Law(
		new CpuCollision(collisionDetector, collisionResolver), 
		useGpu ? new GpuCollision(collisionDetector, collisionResolver
	) : new GpuLaw()),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver) { }
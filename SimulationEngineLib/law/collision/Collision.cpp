#include "law/collision/Collision.h"
#include "law/collision/CpuCollision.h"
#include "law/collision/gpuKernel/GpuCollision.cuh"

Collision::Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool use_gpu) : 
    Law(
		new CpuCollision(collisionDetector, collisionResolver), 
		use_gpu ? new GpuCollision(collisionDetector, collisionResolver
	) : new GpuLaw()),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver) { }
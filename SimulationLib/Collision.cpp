#include "Collision.h"
#include "CpuCollision.h"
#include "GpuCollision.cuh"

Collision::Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver, bool use_gpu) : 
    Law(
		new CpuCollision(collisionDetector, collisionResolver), 
		use_gpu ? new GpuCollision(collisionDetector, collisionResolver
	) : new GpuLaw()),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver) { }
#include "law/collision/Collision.h"
#include "law/collision/CpuCollision.h"
#include "law/collision/gpuKernel/GpuCollision.cuh"

Collision::Collision(
	std::shared_ptr<CollisionDetector> collisionDetector, 
	std::shared_ptr<CollisionResolver> collisionResolver, 
	bool useGpu
) : Law(
		std::make_shared<CpuCollision>(collisionDetector, collisionResolver), 
		useGpu ? std::make_shared<GpuCollision>(collisionDetector, collisionResolver
	) : std::make_shared<GpuLaw>()),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver) { }
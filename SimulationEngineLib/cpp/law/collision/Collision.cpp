#include "cpp/law/collision/Collision.h"
#include "cpp/law/collision/CpuCollision.h"
#include "shared/law/collision/detector/CollisionDetector.cuh"
#include "shared/law/collision/resolver/CollisionResolver.cuh"
#include "cpp/law/GpuLaw.h"
#if defined(USE_GPU) 
	#include "cuda/law/collision/gpuKernel/GpuCollision.cuh"
#else
	#include "gpuMock/law/collision/gpuKernel/GpuCollision.cuh"
#endif

Collision::Collision(
	std::shared_ptr<CollisionDetector> collisionDetector, 
	std::shared_ptr<CollisionResolver> collisionResolver, 
	std::shared_ptr<MomentumService> momentumService,
	bool useGpu
) : Law(
		"Collision",
		std::make_shared<CpuCollision>(
			collisionDetector, 
			collisionResolver,
			momentumService
		),
		useGpu ? std::make_shared<GpuCollision>(
			collisionDetector, 
			collisionResolver,
			momentumService
		) : std::make_shared<GpuLaw>("Collision")
	),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver),
	momentumService(momentumService) { }
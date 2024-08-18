#include "cpp/law/collision/CollisionCoalesce.h"
#include "shared/law/collision/detector/CollisionDetectorSimple.cuh"
#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce(
	std::shared_ptr<MomentumService> momentumService,
	bool useGpu
) :
	Collision(
		std::make_shared<CollisionDetectorSimple>(), 
		std::make_shared<CollisionResolverCoalesce>(momentumService), 
		momentumService,
		useGpu
	) {}

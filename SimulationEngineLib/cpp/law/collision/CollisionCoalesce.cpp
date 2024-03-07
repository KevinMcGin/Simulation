#include "cpp/law/collision/CollisionCoalesce.h"
#include "shared/law/collision/detector/CollisionDetectorSimple.cuh"
#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce(bool useGpu) :
	Collision(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), useGpu) { }

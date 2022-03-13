#include "law/collision/CollisionCoalesce.h"
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce(bool useGpu) :
	Collision(std::make_shared<CollisionDetectorSimple>(), std::make_shared<CollisionResolverCoalesce>(), useGpu) { }

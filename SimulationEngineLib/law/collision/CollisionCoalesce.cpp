#include "law/collision/CollisionCoalesce.h"
#include "law/collision/detector/CollisionDetectorSimple.cuh"
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce(bool useGpu) :
	Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), useGpu) { }

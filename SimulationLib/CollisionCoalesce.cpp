#include "CollisionCoalesce.h"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce(bool use_gpu) :
	Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce(), use_gpu) { }

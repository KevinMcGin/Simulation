#include "CollisionCoalesce.h"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce() :
	Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce())
{

}

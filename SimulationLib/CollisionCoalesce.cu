#include "CollisionCoalesce.cuh"
#include "CollisionDetectorSimple.cuh"
#include "CollisionResolverCoalesce.cuh"


CollisionCoalesce::CollisionCoalesce() :
	Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce())
{

}

#include "CollisionCoalesce.h"
#include "CollisionDetectorSimple.h"
#include "CollisionResolverCoalesce.h"


CollisionCoalesce::CollisionCoalesce() :
	Collision(new CollisionDetectorSimple(), new CollisionResolverCoalesce())
{

}

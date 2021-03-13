#include "CollissionCoalesce.h"
#include "CollisionDetectorSimple.h"
#include "CollisionResolverCoalesce.h"


CollissionCoalesce::CollissionCoalesce() :
	Collission(new CollisionDetectorSimple(), new CollisionResolverCoalesce())
{

}

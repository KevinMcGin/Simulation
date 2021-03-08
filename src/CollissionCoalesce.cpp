#include "CollissionCoalesce.h"
#include "CollisionDetectorSimple.h"
#include "CollisionResolverCoalesce.h"


CollissionCoalesce::CollissionCoalesce() :
	Collission((CollisionDetector*)new CollisionDetectorSimple(), (CollisionResolver*)new CollisionResolverCoalesce())
{

}

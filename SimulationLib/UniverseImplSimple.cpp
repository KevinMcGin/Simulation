#include "UniverseImplSimple.h"
#include "NewtonGravity.h"
#include "NewtonFirstLaw.h"
#include "CollisionCoalesce.h"



UniverseImplSimple::UniverseImplSimple(SimulationInput* input, SimulationOutput* output, unsigned long endTime) : 
	UniverseImpl({ new CollisionCoalesce(), new NewtonGravity(), new NewtonFirstLaw() }, input, output, 1, endTime)
{

}

#include "UniverseImplSimple.h"
#include "NewtonGravity.h"
#include "NewtonFirstLaw.h"
#include "CollissionCoalesce.h"



UniverseImplSimple::UniverseImplSimple(SimulationInput* input, SimulationOutput* output, unsigned long endTime) : 
	UniverseImpl({ new CollissionCoalesce(), new NewtonGravity(), new NewtonFirstLaw() }, input, output, 1, endTime)
{

}

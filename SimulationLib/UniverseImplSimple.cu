#include "UniverseImplSimple.cuh"
#include "NewtonGravity.cuh"
#include "NewtonFirstLaw.cuh"
#include "CollisionCoalesce.cuh"



UniverseImplSimple::UniverseImplSimple(SimulationInput* input, SimulationOutput* output, unsigned long endTime) : 
	UniverseImpl({ new CollisionCoalesce(), new NewtonGravity(), new NewtonFirstLaw }, input, output, 1, endTime) { }

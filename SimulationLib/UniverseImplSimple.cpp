#include "UniverseImplSimple.h"
#include "NewtonGravity.cuh"
#include "NewtonFirstLaw.cuh"
#include "CollisionCoalesce.h"



UniverseImplSimple::UniverseImplSimple(shared_ptr<SimulationInput> input, shared_ptr<SimulationOutput> output, unsigned long endTime) : 
	UniverseImpl({ new CollisionCoalesce(USE_GPU), new NewtonGravity(), new NewtonFirstLaw }, input, output, 1, endTime) { }

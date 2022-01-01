#include "UniverseImplSimple.h"
#include "NewtonGravity.cuh"
#include "NewtonFirstLaw.cuh"
#include "CollisionCoalesce.h"



UniverseImplSimple::UniverseImplSimple(
	shared_ptr<SimulationInput> input, 
	shared_ptr<SimulationOutput> output, 
	unsigned long endTime,  
	Usage use_gpu
) : UniverseImpl(
	{}, 
	input, 
	output, 
	1, 
	endTime, 
	use_gpu
) {
	this->laws = { new CollisionCoalesce(this->use_gpu == TRUE), new NewtonGravity(), new NewtonFirstLaw };
 }

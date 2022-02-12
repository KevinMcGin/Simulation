#include "universe/UniverseImplSimple.h"
#include "law/gravity/NewtonGravity.h"
#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "law/collision/CollisionCoalesce.h"



UniverseImplSimple::UniverseImplSimple(
	shared_ptr<SimulationInput> input, 
	shared_ptr<SimulationOutput> output, 
	unsigned long endTime,  
	Usage useGpu
) : UniverseImpl(
	{}, 
	input, 
	output, 
	1, 
	endTime, 
	useGpu
) {
	this->laws = { new CollisionCoalesce(this->useGpu == TRUE), new NewtonGravity(), new NewtonFirstLaw };
 }

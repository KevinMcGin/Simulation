#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/collision/CollisionCoalesce.h"

UniverseImplSimple::UniverseImplSimple(
	std::shared_ptr<SimulationInput> input, 
	std::shared_ptr<SimulationOutput> output, 
	unsigned long endTime,  
	unsigned int deltaTime,
	Usage useGpu
) : UniverseImpl(
	{}, 
	input, 
	output, 
	deltaTime, 
	endTime, 
	useGpu
) {
	this->laws = { 
		std::make_shared<CollisionCoalesce>(this->useGpu == TRUE),
		std::make_shared<NewtonGravity>(),
		std::make_shared<NewtonFirstLaw>(),
	};
 }

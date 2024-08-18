#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/collision/CollisionCoalesce.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"
#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"

std::shared_ptr<MomentumService> getMomentumService(
	bool isEinsteinMomentum
) {
	if (isEinsteinMomentum) {
		return std::make_shared<EinsteinMomentumService>();
	} else {
		return std::make_shared<NewtonMomentumService>();
	}
}

UniverseImplSimple::UniverseImplSimple(
	std::shared_ptr<SimulationInput> input, 
	std::shared_ptr<SimulationOutput> output, 
	unsigned long endTime,  
	unsigned int deltaTime,
	Usage useGpu,
	bool isEinsteinMomentum
) : UniverseImpl(
	{}, 
	input, 
	output, 
	deltaTime, 
	endTime, 
	useGpu
) {
	auto momentumService = getMomentumService(isEinsteinMomentum);
	this->laws = {
		std::make_shared<CollisionCoalesce>(
			momentumService,
			this->useGpu == TRUE
		),
		std::make_shared<NewtonGravity>(momentumService),
		std::make_shared<NewtonFirstLaw>(),
	};
 }

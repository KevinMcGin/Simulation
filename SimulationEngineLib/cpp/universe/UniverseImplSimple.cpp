#include "cpp/universe/UniverseImplSimple.h"
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/law/collision/CollisionCoalesce.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"
#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"

namespace {
	std::shared_ptr<MomentumService> getMomentumService(
		MomentumModel momentum
	) {
		if (momentum == MOMENTUM_EINSTEIN) {
			return std::make_shared<EinsteinMomentumService>();
		} else {
			return std::make_shared<NewtonMomentumService>();
		}
	}

	// One momentum service shared by every law that needs one, so a run
	// cannot end up resolving collisions relativistically while accelerating
	// under gravity classically.
	//
	// The order is the engine's, not the caller's: collisions are resolved
	// on the positions the last frame ended at, gravity then accelerates
	// what survived, and the first law finally moves everything. Enabling a
	// law only inserts it into that fixed sequence.
	std::vector<std::shared_ptr<Law>> buildLaws(
		const LawConfig& lawConfig,
		bool useGpu
	) {
		auto momentumService = getMomentumService(lawConfig.momentum);
		std::vector<std::shared_ptr<Law>> laws;
		if (lawConfig.isCollisionCoalesceEnabled) {
			laws.push_back(std::make_shared<CollisionCoalesce>(momentumService, useGpu));
		}
		if (lawConfig.isNewtonGravityEnabled) {
			laws.push_back(std::make_shared<NewtonGravity>(momentumService, lawConfig.gravitationalConstant));
		}
		if (lawConfig.isNewtonFirstLawEnabled) {
			laws.push_back(std::make_shared<NewtonFirstLaw>());
		}
		return laws;
	}
}

UniverseImplSimple::UniverseImplSimple(
	std::shared_ptr<SimulationInput> input, 
	std::shared_ptr<SimulationOutput> output, 
	unsigned long endTime,  
	unsigned int deltaTime,
	Usage useGpu,
	const LawConfig& lawConfig
) : UniverseImpl(
	{}, 
	input, 
	output, 
	deltaTime, 
	endTime, 
	useGpu
) {
	this->laws = buildLaws(lawConfig, this->useGpu == TRUE);
}

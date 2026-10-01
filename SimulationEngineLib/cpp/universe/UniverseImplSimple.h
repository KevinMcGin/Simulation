#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/law/LawConfig.h"
#include "cpp/universe/UniverseImpl.h"
#include "cpp/universe/input/SimulationInput.h"

#include <vector>

class UniverseImplSimple : public UniverseImpl {
public:
	UniverseImplSimple(
		std::shared_ptr<SimulationInput> input, 
		std::shared_ptr<SimulationOutput> output, 
		unsigned long endTime,
		Real deltaTime = 1.0,
		Usage useGpu = UNDEFINED,
		const LawConfig& lawConfig = LawConfig()
	);
};

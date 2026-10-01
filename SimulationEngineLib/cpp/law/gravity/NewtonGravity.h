#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/law/Law.h"
#include "cpp/constant/PhysicalConstants.h"
#include "shared/service/momentum/MomentumService.cuh"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonGravity: public Law {
public:
	NewtonGravity(
		std::shared_ptr<MomentumService> momentumService,
		Real G = PhysicalConstants::GRAVITATIONAL_CONSTANT
	);
protected:
	const Real G;
};
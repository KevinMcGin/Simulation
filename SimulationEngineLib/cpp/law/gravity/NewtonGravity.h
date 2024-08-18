#pragma once
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
		float G = PhysicalConstants::GRAVITATIONAL_CONSTANT
	);
protected:
	const float G;
};
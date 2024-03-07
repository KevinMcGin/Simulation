#pragma once
#include "cpp/law/Law.h"
#include "cpp/constant/PhysicalConstants.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonGravity: public Law {
public:
	NewtonGravity(float G = PhysicalConstants::GRAVITATIONAL_CONSTANT);
protected:
	const float G;
};
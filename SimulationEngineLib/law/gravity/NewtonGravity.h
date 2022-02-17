#pragma once
#include "law/Law.h"
#include "constant/PhysicalConstants.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonGravity: public Law {
public:
	NewtonGravity(float G = PhysicalConstants::GRAVITATIONAL_CONSTANT);
protected:
	const float G;
};
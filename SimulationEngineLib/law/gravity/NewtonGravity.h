#pragma once
#include "law/Law.h"
#include "constant/PhysicalConstants.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonGravity: public Law {
public:
	NewtonGravity(double G = PhysicalConstants::GRAVITATIONAL_CONSTANT);
protected:
	const double G;
};
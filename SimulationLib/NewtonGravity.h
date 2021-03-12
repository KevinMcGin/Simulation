#pragma once
#include "Law.h"

#include <vector>
#include <stdio.h>
#include <iostream>

const double GRAVITATIONAL_CONSTANT = 0.00005;

class NewtonGravity: public Law {
public:
	NewtonGravity(double G = GRAVITATIONAL_CONSTANT);

	virtual void run(vector<Particle*>& particles);

protected:
	const double G;

private:
	double getAcceleration(double mass, double displacement);
};
#pragma once
#include "Law.h"
#include "PhysicalConstants.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class NewtonGravity: public Law {
public:
	NewtonGravity();
	NewtonGravity(double G);

	virtual void run(vector<Particle*>& particles);
	virtual void runParallel(vector<Particle*>& particles);

protected:
	const double G;
};

class CopyClass {
public:
  Particle ** par;
};
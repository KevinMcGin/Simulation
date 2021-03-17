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

protected:
	const double G;

private:
	Vector3D getRadiusComponent(Vector3D position1, Vector3D position2);
};
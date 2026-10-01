#pragma once
#include "shared/precision/Real.cuh"
#include "shared/particle/model/Vector3D.cuh"



class Distribution3D {
public:
	Distribution3D() { };

	virtual  Vector3D<Real> getValue() = 0;

};
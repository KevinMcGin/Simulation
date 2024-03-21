#pragma once
#include "shared/particle/model/Vector3D.cuh"



class Distribution3D {
public:
	Distribution3D() { };

	virtual  Vector3D<float> getValue() = 0;

};
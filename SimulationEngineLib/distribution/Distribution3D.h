#pragma once
#include "particle/model/Vector3D.cuh"



class Distribution3D {
public:
	Distribution3D() { };

	virtual  Vector3D getValue() = 0;

};
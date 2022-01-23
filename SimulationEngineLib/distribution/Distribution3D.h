#pragma once
#include "particle/model/Vector3D.cuh"

using namespace std;

class Distribution3D {
public:
	Distribution3D() { };

	virtual  Vector3D getValue() = 0;

};
#pragma once
#include "Vector3D.h"

using namespace std;

class Distribution3D {
public:
	Distribution3D() { };

	virtual  Vector3D getValue() = 0;

};
#pragma once
#include "shared/precision/Real.cuh"
#include <stdlib.h>   
#include <time.h>

class Distribution {
public:
	Distribution() { srand( (unsigned int)time(nullptr) ); };
	virtual ~Distribution() = default;

	virtual Real getValue() = 0;
	
	static Real random(Real mean, Real delta);
	static Real random(Real delta);
};
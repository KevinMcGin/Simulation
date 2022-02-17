#pragma once
#include <stdlib.h>   
#include <time.h>

class Distribution {
public:
	Distribution() { srand( (unsigned int)time(nullptr) ); };
	virtual ~Distribution() = default;

	virtual float getValue() = 0;
	
	static float random(float mean, float delta);
	static float random(float delta);
};
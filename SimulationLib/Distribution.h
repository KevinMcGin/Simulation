#pragma once
#include <stdlib.h>   
#include <time.h>

class Distribution {
public:
	Distribution() { srand(time(NULL)); };

	virtual double getValue() = 0;
	
	static double random(double mean, double delta);
	static double random(double delta);
};
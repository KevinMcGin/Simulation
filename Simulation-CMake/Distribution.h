#pragma once
#include <stdlib.h>   
#include <time.h>

class Distribution {
public:
	Distribution() { srand(time(NULL)); };

	virtual double getValue() = 0;

protected:
	double random(double mean, double delta);
};
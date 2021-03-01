#pragma once
#include <stdlib.h>   
#include <time.h>

class Distribution {
public:
	Distribution() { { srand(time(NULL)); } };

	virtual double getValue() = 0;

protected:
	double random(double mean, double delta) {
		const double deltaRand = ((double)rand() / RAND_MAX) * 2 * delta - delta;
		return mean + deltaRand;
	}
};
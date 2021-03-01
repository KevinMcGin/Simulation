#pragma once
#include <stdlib.h>   
#include <time.h> 
#include <array>

using namespace std;

class Distribution3D {
public:
	Distribution3D() { srand(time(NULL)); };

	virtual  array<double, 3> getValue() = 0;
protected:
	//TODO: random model
	double random(double mean, double delta) {
		const double deltaRand = ((double)rand() / RAND_MAX) * 2 * delta - delta;
		return mean + deltaRand;
	}

};
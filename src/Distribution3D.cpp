#include "Distribution3D.h"



double Distribution3D::randomFromMean(double mean, double delta)
{
	const double deltaRand = ((double)rand() / RAND_MAX) * 2 * delta - delta;
	return mean + deltaRand;
}

double Distribution3D::random(double delta)
{
	return ((double)rand() / RAND_MAX) * delta;
}


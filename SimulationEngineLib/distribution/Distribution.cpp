#include "distribution/Distribution.h"

double Distribution::random(double mean, double delta)
{
	const double deltaRand = ((double)rand() / RAND_MAX) * 2 * delta - delta;
	return mean + deltaRand;
}

double Distribution::random(double delta)
{
	return ((double)rand() / RAND_MAX) * delta;
}

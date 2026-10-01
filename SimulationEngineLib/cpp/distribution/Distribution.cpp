#include "cpp/distribution/Distribution.h"

Real Distribution::random(Real mean, Real delta)
{
	const Real deltaRand = ((Real)rand() / RAND_MAX) * 2 * delta - delta;
	return mean + deltaRand;
}

Real Distribution::random(Real delta)
{
	return ((Real)rand() / RAND_MAX) * delta;
}

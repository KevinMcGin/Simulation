#include "Distribution3D.h"



double Distribution3D::random(double mean, double delta)
{
	const double deltaRand = ((double)rand() / RAND_MAX) * 2 * delta - delta;
	return mean + deltaRand;
}

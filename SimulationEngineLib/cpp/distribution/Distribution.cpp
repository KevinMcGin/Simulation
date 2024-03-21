#include "cpp/distribution/Distribution.h"

float Distribution::random(float mean, float delta)
{
	const float deltaRand = ((float)rand() / RAND_MAX) * 2 * delta - delta;
	return mean + deltaRand;
}

float Distribution::random(float delta)
{
	return ((float)rand() / RAND_MAX) * delta;
}

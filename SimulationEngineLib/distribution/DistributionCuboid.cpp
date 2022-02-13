#include "distribution/DistributionCuboid.h"
#include "distribution/Distribution.h"


Vector3D<float> DistributionCuboid::getValue()
{
	return { 
		Distribution::random(mean.x, delta.x), 
		Distribution::random(mean.y, delta.y), 
		Distribution::random(mean.z, delta.z) };
}

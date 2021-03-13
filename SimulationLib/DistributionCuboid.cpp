#include "DistributionCuboid.h"
#include "Distribution.h"


Vector3D DistributionCuboid::getValue()
{
	return { 
		Distribution::random(mean.x, delta.x), 
		Distribution::random(mean.y, delta.y), 
		Distribution::random(mean.z, delta.z) };
}

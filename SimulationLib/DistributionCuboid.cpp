#include "DistributionCuboid.h"



Vector3D DistributionCuboid::getValue()
{
	return { randomFromMean(mean.x, delta.x), randomFromMean(mean.y, delta.y), randomFromMean(mean.z, delta.z) };
}

#include "DistributionGlobe.h"



Vector3D DistributionGlobe::getValue()
{
	return { random(mean.x, delta.x), random(mean.y, delta.y), random(mean.z, delta.z) };
}

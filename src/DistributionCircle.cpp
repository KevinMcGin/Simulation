#include "DistributionCircle.h"



DistributionCircle::DistributionCircle(Vector3D mean, double delta) : DistributionGlobe(mean, { delta, delta, 0 })
{

}

Vector3D DistributionCircle::getValue()
{
	double theta = randomFromMean(M_PI, M_PI);

	return { mean.x + random(delta.x) * cos(theta),
		mean.y + random(delta.y) * sin(theta),
		mean.z
	};
}

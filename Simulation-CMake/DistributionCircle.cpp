#include "DistributionCircle.h"



DistributionCircle::DistributionCircle(Vector3D mean, double delta) : DistributionSphere(mean, delta)
{

}

Vector3D DistributionCircle::getValue()
{
	double theta = randomFromMean(M_PI, M_PI);
	double magnitude = random(delta);

	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z
	};
}

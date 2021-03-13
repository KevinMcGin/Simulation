#include "DistributionCircle.h"
#include "Distribution.h"

DistributionCircle::DistributionCircle(Vector3D mean, double delta) : DistributionSphere(mean, delta)
{

}

Vector3D DistributionCircle::getValue()
{
	double theta = Distribution::random(M_PI, M_PI);
	double magnitude = Distribution::random(delta);

	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z
	};
}

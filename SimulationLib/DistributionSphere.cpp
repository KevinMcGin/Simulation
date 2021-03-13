#include "DistributionSphere.h"
#include "Distribution.h"


DistributionSphere::DistributionSphere(Vector3D mean, double delta) : Distribution3D(),
	mean(mean), delta(delta)
{

}

Vector3D DistributionSphere::getValue()
{
	double theta = Distribution::random(M_PI, M_PI);
	double magnitude = Distribution::random(delta);

	//Is it ok to have these mean terms all unique in this equation?
	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z 
	};
}

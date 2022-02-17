#include "distribution/DistributionSphere.h"
#include "distribution/Distribution.h"


DistributionSphere::DistributionSphere(Vector3D<float> mean, float delta) : Distribution3D(),
	mean(mean), delta(delta)
{

}

Vector3D<float> DistributionSphere::getValue()
{
	float theta = Distribution::random(M_PI, M_PI);
	float magnitude = Distribution::random(delta);

	//Is it ok to have these mean terms all unique in this equation?
	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z 
	};
}

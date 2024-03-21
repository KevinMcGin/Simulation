#include "cpp/distribution/DistributionCircle.h"
#include "cpp/distribution/Distribution.h"

DistributionCircle::DistributionCircle(Vector3D<float> mean, float delta) : DistributionSphere(mean, delta)
{

}

Vector3D<float> DistributionCircle::getValue()
{
	float theta = Distribution::random(M_PI, M_PI);
	float magnitude = Distribution::random(delta);

	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z
	};
}

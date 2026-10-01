#define _USE_MATH_DEFINES
#include "cpp/distribution/DistributionCircle.h"
#include "cpp/distribution/Distribution.h"

DistributionCircle::DistributionCircle(Vector3D<Real> mean, Real delta) : DistributionSphere(mean, delta)
{

}

Vector3D<Real> DistributionCircle::getValue()
{
	Real theta = Distribution::random(M_PI, M_PI);
	Real magnitude = Distribution::random(delta);

	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z
	};
}

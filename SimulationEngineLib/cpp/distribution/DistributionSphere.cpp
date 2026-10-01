#define _USE_MATH_DEFINES
#include "cpp/distribution/DistributionSphere.h"
#include "cpp/distribution/Distribution.h"


DistributionSphere::DistributionSphere(Vector3D<Real> mean, Real delta) : Distribution3D(),
	mean(mean), delta(delta)
{

}

Vector3D<Real> DistributionSphere::getValue()
{
	Real theta = Distribution::random(M_PI, M_PI);
	Real magnitude = Distribution::random(delta);

	//Is it ok to have these mean terms all unique in this equation?
	return { mean.x + magnitude * cos(theta),
		mean.y + magnitude * sin(theta),
		mean.z 
	};
}

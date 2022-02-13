#include "distribution/DistributionGlobe.h"
#include "distribution/Distribution.h"

Vector3D<float> DistributionGlobe::getValue()
{
	float theta = Distribution::random(M_PI, M_PI);
	float phi =  Distribution::random(M_PI, M_PI);

	//Is it ok to have these mean terms all unique in this equation?
	return { mean.x +  Distribution::random(delta.x) * cos(theta)*sin(phi), 
		mean.y +  Distribution::random(delta.y) * sin(theta)*sin(phi),
		mean.z +  Distribution::random(delta.z) * cos(phi)
	};
}

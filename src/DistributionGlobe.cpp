#include "DistributionGlobe.h"

Vector3D DistributionGlobe::getValue()
{
	double theta = randomFromMean(M_PI, M_PI);
	double phi = randomFromMean(M_PI, M_PI);

	//Is it ok to have these mean terms all unique in this equation?
	return { mean.x + random(delta.x) * cos(theta)*sin(phi), 
		mean.y + random(delta.y) * sin(theta)*sin(phi),
		mean.z + random(delta.z) * cos(phi)
	};
}

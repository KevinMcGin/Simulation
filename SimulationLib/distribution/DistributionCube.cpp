#include "distribution/DistributionCube.h"

DistributionCube::DistributionCube(Vector3D mean, double delta) : DistributionCuboid(mean, { delta, delta, delta })
{

}
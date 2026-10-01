#include "cpp/distribution/DistributionCube.h"

DistributionCube::DistributionCube(Vector3D<Real> mean, Real delta) : DistributionCuboid(mean, { delta, delta, delta })
{

}
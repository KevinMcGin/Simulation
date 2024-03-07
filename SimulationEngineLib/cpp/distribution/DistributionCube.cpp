#include "cpp/distribution/DistributionCube.h"

DistributionCube::DistributionCube(Vector3D<float> mean, float delta) : DistributionCuboid(mean, { delta, delta, delta })
{

}
#include "cpp/distribution/DistributionSquare.h"



DistributionSquare::DistributionSquare(Vector3D<float> mean, float delta) : DistributionCuboid(mean, { delta, delta, 0 })
{

}

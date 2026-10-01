#include "cpp/distribution/DistributionSquare.h"



DistributionSquare::DistributionSquare(Vector3D<Real> mean, Real delta) : DistributionCuboid(mean, { delta, delta, 0 })
{

}

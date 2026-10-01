#include "cpp/distribution/DistributionSimple.h"



Real DistributionSimple::getValue()
{
	return Distribution::random(mean, delta);
}

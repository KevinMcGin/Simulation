#include "cpp/distribution/DistributionSimple.h"



float DistributionSimple::getValue()
{
	return Distribution::random(mean, delta);
}

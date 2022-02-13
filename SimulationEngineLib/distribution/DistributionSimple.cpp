#include "distribution/DistributionSimple.h"



float DistributionSimple::getValue()
{
	return Distribution::random(mean, delta);
}

#include "DistributionSimple.h"



double DistributionSimple::getValue()
{
	return Distribution::random(mean, delta);
}

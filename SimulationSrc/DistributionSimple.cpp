#include "DistributionSimple.h"



double DistributionSimple::getValue()
{
	return random(mean, delta);
}

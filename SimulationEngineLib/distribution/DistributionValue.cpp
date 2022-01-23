#include "distribution/DistributionValue.h"

DistributionValue::DistributionValue(double value) : Distribution(),
	value(value)
{

}

double DistributionValue::getValue()
{
	return value;
}

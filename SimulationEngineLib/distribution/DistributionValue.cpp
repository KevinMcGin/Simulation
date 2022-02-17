#include "distribution/DistributionValue.h"

DistributionValue::DistributionValue(float value) : Distribution(),
	value(value)
{

}

float DistributionValue::getValue()
{
	return value;
}

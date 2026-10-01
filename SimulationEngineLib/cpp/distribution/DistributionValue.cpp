#include "cpp/distribution/DistributionValue.h"

DistributionValue::DistributionValue(Real value) : Distribution(),
	value(value)
{

}

Real DistributionValue::getValue()
{
	return value;
}

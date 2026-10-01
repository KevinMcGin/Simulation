#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/Distribution.h"

class DistributionSimple: public Distribution {
public:
	DistributionSimple(Real mean, Real delta) : Distribution(),
		mean(mean),
		delta(delta) {};


	Real getValue() override;

private:
	const Real mean;
	const Real delta;

};
#pragma once
#include "Distribution.h"

class DistributionSimple: public Distribution {
public:
	DistributionSimple(double mean, double delta) : Distribution(),
		mean(mean),
		delta(delta) {};


	virtual double getValue();

private:
	const double mean;
	const double delta;

};
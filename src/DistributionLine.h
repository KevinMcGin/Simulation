#pragma once
#include "Distribution.h"

class DistributionLine: public Distribution {
public:
	DistributionLine(double mean, double delta) : Distribution(),
		mean(mean),
		delta(delta) {};


	virtual double getValue() {
		return random(mean, delta);
	}

private:
	const double mean;
	const double delta;

};
#pragma once
#include "distribution/Distribution.h"

class DistributionSimple: public Distribution {
public:
	DistributionSimple(float mean, float delta) : Distribution(),
		mean(mean),
		delta(delta) {};


	float getValue() override;

private:
	const float mean;
	const float delta;

};
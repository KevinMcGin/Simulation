#define _USE_MATH_DEFINES
#include "cpp/distribution/DistributionAnnulus.h"
#include "cpp/distribution/Distribution.h"

#include <algorithm>
#include <cmath>
#include <limits>

DistributionAnnulus::DistributionAnnulus(
	Vector3D<float> mean,
	float innerRadius,
	float outerRadius,
	float bias
) : Distribution3D(),
	mean(mean),
	// An inner radius past the outer one describes no ring at all; clamped
	// rather than rejected, so it degenerates to the circle at the outer
	// radius instead of sampling an inverted range forever.
	innerRadius(std::min(innerRadius, outerRadius)),
	outerRadius(outerRadius),
	bias(std::clamp(bias, 0.0f, 1.0f))
{
}

// bias 0.5 gives 1, which leaves the sample untouched and so spreads
// particles evenly across the ring — the behaviour before the bias existed.
// Below 0.5 the exponent grows, pulling the sample towards 0 (the inner
// edge); above 0.5 it shrinks towards 0, pushing it towards the outer edge.
//
// Both ends are allowed and mean the ring collapsing to a single circle: at
// 1 the exponent is 0, which puts every sample on the outer radius, and at
// 0 it is infinite, which is the same statement about the inner one. The
// infinity is returned as itself rather than arrived at by dividing by
// zero, and getValue reads it rather than feeding it to pow — an optimiser
// told it may assume finite arithmetic is free to get that wrong.
float DistributionAnnulus::biasExponent(float bias) {
	const float clamped = std::clamp(bias, 0.0f, 1.0f);
	if (clamped == 0.0f) {
		return std::numeric_limits<float>::infinity();
	}
	return (1.0f - clamped) / clamped;
}

Vector3D<float> DistributionAnnulus::getValue() {
	const float theta = Distribution::random(M_PI, M_PI);
	const float unitRadius = Distribution::random(1.0f);
	const float exponent = biasExponent(bias);
	// An infinite exponent is the whole ring collapsing onto its inner edge.
	// Taken as a case of its own so that it doesn't depend on pow answering
	// an infinite power the way IEEE says it should — including for the
	// unitRadius of exactly 1 the sampler can return, where it wouldn't.
	const float acrossRing = std::isinf(exponent) ? 0.0f : std::pow(unitRadius, exponent);
	const float magnitude = innerRadius + (outerRadius - innerRadius) * acrossRing;

	return {
		mean.x + magnitude * std::cos(theta),
		mean.y + magnitude * std::sin(theta),
		mean.z
	};
}

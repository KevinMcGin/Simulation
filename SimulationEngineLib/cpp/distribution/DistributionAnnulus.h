#pragma once
#include "shared/precision/Real.cuh"
#include "cpp/distribution/Distribution3D.h"

// A point in the ring between an inner and an outer radius, at a uniformly
// random angle. The radius itself is not uniform unless asked to be: bias
// says where in the ring particles gather, on a 0..1 scale where 0.5 spreads
// them evenly over it, below 0.5 crowds them towards the inner edge and
// above 0.5 towards the outer one. The ends are included, and are the ring
// collapsing to a single circle: everything on the inner radius at 0, and
// on the outer radius at 1.
class DistributionAnnulus : public Distribution3D {
public:
	DistributionAnnulus(
		Vector3D<Real> mean,
		Real innerRadius,
		Real outerRadius,
		Real bias = 0.5
	);

	Vector3D<Real> getValue() override;

	// The power the uniform 0..1 sample is raised to before it is stretched
	// across the ring, which is infinite at a bias of 0. Exposed for the
	// tests, which would otherwise only be able to check the bias through
	// the spread of a sample.
	static Real biasExponent(Real bias);

private:
	const Vector3D<Real> mean;
	const Real innerRadius;
	const Real outerRadius;
	const Real bias;
};

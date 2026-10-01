#include "shared/law/collision/detector/CollisionDetectorSimple.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif
bool CollisionDetectorSimple::isCollision(Particle* p1, Particle* p2)
{
	Vector3D<Real> difference = p1->position - p2->position;
	Real magnitudeSquared = difference.magnitudeSquared();
	return magnitudeSquared < pow(p1->radius + p2->radius, 2);
}

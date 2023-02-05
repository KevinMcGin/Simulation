#include "law/collision/detector/CollisionDetectorSimple.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif
bool CollisionDetectorSimple::isCollision(Particle* p1, Particle* p2)
{
	Vector3D<float> difference = p1->position - p2->position;
	float magnitudeSquared = difference.magnitudeSquared();
	return magnitudeSquared < pow(p1->radius + p2->radius, 2);
}

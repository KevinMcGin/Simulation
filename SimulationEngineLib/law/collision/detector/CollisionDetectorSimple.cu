#include "law/collision/detector/CollisionDetectorSimple.cuh"

__device__ __host__
bool CollisionDetectorSimple::isCollision(Particle* p1, Particle* p2)
{
	Vector3D<float> difference = p1->position - p2->position;
	float magnitudeSquared = difference.magnitudeSquared();
	return magnitudeSquared < pow(p1->radius + p2->radius, 2);
}

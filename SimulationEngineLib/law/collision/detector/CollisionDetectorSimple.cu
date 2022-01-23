#include "law/collision/detector/CollisionDetectorSimple.cuh"

__device__ __host__
bool CollisionDetectorSimple::isCollision(Particle* p1, Particle* p2)
{
	Vector3D difference = p1->position - p2->position;
	return difference.magnitudeSquared() < pow(p1->radius + p2->radius, 2);
}

#include "CollisionDetectorSimple.cuh"

__device__ __host__
bool CollisionDetectorSimple::isCollision(Particle* p1, Particle* p2)
{
	Vector3D difference = p1->position - p2->position;
	double absoluteDifference = sqrt(pow(difference.x, 2) + pow(difference.y, 2) + pow(difference.z, 2));
	return absoluteDifference < p1->radius + p2->radius;
}

#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"

#if defined(USE_GPU)
   __device__ __host__
#endif
void CollisionResolverCoalesce::resolve(Particle* p1, Particle* p2) {
	p1->radius = pow(pow(p1->radius, 3) + pow(p2->radius, 3), 1 / 3.0);
	p1->position = getCoalesced(p1->mass, p2->mass, p1->position, p2->position);
	p1->velocity = getCoalesced(p1->mass, p2->mass, p1->velocity, p2->velocity);
	// p1->angularVelocity = getCoalesced(p1->mass, p2->mass, p1->angularVelocity, p2->angularVelocity);
	p1->mass = p1->mass + p2->mass;
	p2->deleted = true;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
Vector3D<float> CollisionResolverCoalesce::getCoalesced(float mass1, float mass2, Vector3D<float> vec1, Vector3D<float> vec2) {
	return (mass1 * vec1 + mass2 * vec2) / (mass1 + mass2);
}

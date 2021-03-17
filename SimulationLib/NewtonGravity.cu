#include "NewtonGravity.cuh"
#include <cmath>



NewtonGravity::NewtonGravity() : Law(), G(PhysicalConstants::GRAVITATIONAL_CONSTANT)
{

}

NewtonGravity::NewtonGravity(double G) : Law(), G(G)
{

}

__global__ 
static void newtonGravityKernel(Particle** particles, int particleMatchingsCount)
{
	int idx = threadIdx.x + blockIdx.x*blockDim.x;
	if(idx < particleMatchingsCount) { 
		//runParticle(p1,p2);
	} 
}

void NewtonGravity::run(vector<Particle*>& particles)
{
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
		for (auto it2 = it1+1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			runParticle(p1,p2);
		}
	}

}

__device__ __host__ 
void NewtonGravity::runParticle(Particle* p1, Particle* p2) {	
	Vector3D displacement = (p2->position - p1->position);
	double displacementSquared = displacement.magnitudeSquared();
	Vector3D radiusComponent = getRadiusComponent(p1->position, p2->position);
	Vector3D acceleration1 = p2->mass * radiusComponent;
	p1->velocity = p1->velocity + acceleration1;
	Vector3D acceleration2 = p1->mass * radiusComponent * -1;
	p2->velocity = p2->velocity + acceleration2;
}

__device__ __host__ 
Vector3D NewtonGravity::getRadiusComponent(Vector3D position1, Vector3D position2)
{
	Vector3D displacement = position2 - position1;
	double displacementSquared = displacement.magnitudeSquared();
	if (displacementSquared == 0 ) return {0,0,0};
	return (G / displacementSquared) * displacement.unit();
}

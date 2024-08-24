#include "gpuMock/law/collision/gpuKernel/GpuCollision.cuh"

GpuCollision::GpuCollision(
	std::shared_ptr<CollisionDetector> collisionDetector, 
	std::shared_ptr<CollisionResolver> collisionResolver,	
	std::shared_ptr<MomentumService> momentumService
) : 
	GpuLaw("Collision") {}

GpuCollision::~GpuCollision() {}

void GpuCollision::run(
	Particle** particles, 
	int particleCount,
	unsigned int deltaTime
) {}
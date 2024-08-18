#pragma once
#include "shared/particle/Particle.cuh"
#include "shared/service/momentum/MomentumService.cuh"
#include <vector>


class CollisionResolver {
public:
#if defined(USE_GPU)
   __device__ __host__
#endif
   CollisionResolver(std::shared_ptr<MomentumService> momentumService) : 
      momentumService(momentumService) {}
#if defined(USE_GPU)
   __device__ __host__
#endif
virtual void resolve(
   Particle* p1, 
   Particle* p2,
	MomentumService* momentumService
) = 0;
	virtual int getIndex() = 0;

protected:
   std::shared_ptr<MomentumService> momentumService;
};
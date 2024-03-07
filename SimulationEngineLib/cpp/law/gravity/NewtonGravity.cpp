#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/law/gravity/CpuNewtonGravity.h"
#include "cuda/law/gravity/gpuKernel/GpuNewtonGravity.cuh"


NewtonGravity::NewtonGravity(float G) : Law(std::make_shared<CpuNewtonGravity>(G), std::make_shared<GpuNewtonGravity>(G)), 
	G(G) { }

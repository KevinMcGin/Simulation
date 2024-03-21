#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/law/gravity/CpuNewtonGravity.h"
#include "cpp/law/GpuLaw.h"
#if defined(USE_GPU) 
	#include "cuda/law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#else
	#include "gpuMock/law/gravity/gpuKernel/GpuNewtonGravity.cuh"
#endif


NewtonGravity::NewtonGravity(float G) : Law(
	"NewtonGravity",
	std::make_shared<CpuNewtonGravity>(G),
	std::make_shared<GpuNewtonGravity>(G)
), 
	G(G) { }

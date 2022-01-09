#include "law/gravity/NewtonGravity.h"
#include "law/gravity/CpuNewtonGravity.h"
#include "law/gravity/gpuKernel/GpuNewtonGravity.cuh"


NewtonGravity::NewtonGravity(double G) : Law(new CpuNewtonGravity(G), new GpuNewtonGravity(G)), 
	G(G) { }

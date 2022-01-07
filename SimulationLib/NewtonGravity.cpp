#include "NewtonGravity.h"
#include "CpuNewtonGravity.h"
#include "GpuNewtonGravity.cuh"


NewtonGravity::NewtonGravity(double G) : Law(new CpuNewtonGravity(G), new GpuNewtonGravity(G)), 
	G(G) { }

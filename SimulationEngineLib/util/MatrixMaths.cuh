#pragma once
#if defined(USE_GPU)
    #include "cuda_runtime.h"
#endif

class MatrixMaths {
public:
#if defined(USE_GPU)
   __device__ __host__
#endif 
static void getLowerTriangularCoordinates(unsigned long long i, unsigned long long* x, unsigned long long* y);

#if defined(USE_GPU)
   __device__ __host__
#endif 
static unsigned long long getUpperTriangularIndex(unsigned long long x, unsigned long long y);

#if defined(USE_GPU)
   __device__ __host__
#endif 
static unsigned long long getLowerTriangularIndex(unsigned long long x, unsigned long long y);

};
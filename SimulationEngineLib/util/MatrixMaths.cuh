#pragma once
#include "cuda_runtime.h"

class MatrixMaths {
public:
    __device__ __host__ static void getLowerTriangularCoordinates(unsigned long long i, unsigned long long* x, unsigned long long* y);
    __device__ __host__ static unsigned long long getUpperTriangularIndex(unsigned long long x, unsigned long long y);
    __device__ __host__ static unsigned long long getLowerTriangularIndex(unsigned long long x, unsigned long long y);
};
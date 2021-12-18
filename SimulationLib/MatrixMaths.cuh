#pragma once
#include "cuda_runtime.h"

class MatrixMaths {
public:
    __device__ __host__ static void getLowerTriangularCoordinates(int i, int* x, int* y);
    __device__ __host__ static int getUpperTriangularIndx(int x, int y);
    __device__ __host__ static int getLowerTriangularIndx(int x, int y);
};
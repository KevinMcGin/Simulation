#include "util/MatrixMaths.cuh"

#include <cmath>

#if defined(USE_GPU)
   __device__ __host__
#endif
void MatrixMaths::getLowerTriangularCoordinates(unsigned long long i, unsigned long long* x, unsigned long long* y) {
    *y = (unsigned long long)(((-1+sqrt((double)8*i+1))/2) + 1);
    *x = i - (*y-1)*(*y)/2;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
unsigned long long MatrixMaths::getUpperTriangularIndex(unsigned long long x, unsigned long long y) {
    return y + (x-1)*x/2;
}

#if defined(USE_GPU)
   __device__ __host__
#endif
unsigned long long MatrixMaths::getLowerTriangularIndex(unsigned long long x, unsigned long long y) {
    return getUpperTriangularIndex(y, x);
}
#include "MatrixMaths.cuh"

#include <cmath>

__device__ __host__
void MatrixMaths::getLowerTriangularCoordinates(int i, int* x, int* y) {
    *y = ((-1+sqrt((double)8*i+1))/2) + 1;
    *x = i - (*y-1)*(*y)/2;
}

__device__ __host__
int MatrixMaths::getUpperTriangularIndex(int x, int y) {
    return y + (x-1)*x/2;
}

__device__ __host__
int MatrixMaths::getLowerTriangularIndex(int x, int y) {
    return getUpperTriangularIndex(y, x);
}
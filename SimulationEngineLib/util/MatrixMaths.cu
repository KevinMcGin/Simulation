#include "util/MatrixMaths.cuh"

#include <cmath>
#include< cstdio>
using namespace std;

__device__ __host__
void MatrixMaths::getLowerTriangularCoordinates(unsigned long long i, unsigned long long* x, unsigned long long* y) {
    *y = ((-1+sqrt((double)8*i+1))/2) + 1;
    *x = i - (*y-1)*(*y)/2;
}

__device__ __host__
unsigned long long MatrixMaths::getUpperTriangularIndex(unsigned long long x, unsigned long long y) {
    return y + (x-1)*x/2;
}

__device__ __host__
unsigned long long MatrixMaths::getLowerTriangularIndex(unsigned long long x, unsigned long long y) {
    return getUpperTriangularIndex(y, x);
}
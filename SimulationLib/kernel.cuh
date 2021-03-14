#pragma once
//#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

class kernel {

    cudaError_t addWithCuda(int* c, const int* a, const int* b, unsigned int size);
};

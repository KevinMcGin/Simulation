#pragma once
#include "cuda_runtime.h"

#include <string>

using namespace std;

class CudaWithError {
public:
    CudaWithError(string className);
    void setDevice(int device);
    void malloc(void** devPtr, size_t size);
    void memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind);
    void deviceSynchronize();
    void cudaFree(void* devPtr);
private: 
    string className;
    void throwErrorMaybe(cudaError_t cudaStatus, string error);
};

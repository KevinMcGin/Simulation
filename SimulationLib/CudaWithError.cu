#include "CudaWithError.cuh"
#include<iostream>


CudaWithError::CudaWithError(string className): className(className) { }

void CudaWithError::throwErrorMaybe(cudaError_t cudaStatus, string error) {
    if (cudaStatus != cudaSuccess) {
        string totalError = className + ": " + error + "\n" + cudaGetErrorString(cudaStatus);
        cerr << endl << totalError;
        throw new runtime_error(totalError);
    }
}

void CudaWithError::setDevice(int device) {
	cudaError_t cudaStatus = cudaSetDevice(device);
    throwErrorMaybe(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
}

void CudaWithError::malloc(void** devPtr, size_t size) {
    cudaError_t cudaStatus = cudaMalloc(devPtr, size);
    throwErrorMaybe(cudaStatus, "cudaMalloc failed!");
}

void CudaWithError::memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind) {
    cudaError_t cudaStatus = cudaMemcpy(dst, src, count, kind);
    throwErrorMaybe(cudaStatus, "cudaMemcpy failed!");
}

void CudaWithError::deviceSynchronize() {
    cudaError_t cudaStatus = cudaDeviceSynchronize();
    throwErrorMaybe(cudaStatus, "cudaDeviceSynchronize failed!");
}

void CudaWithError::free(void* devPtr) {
    cudaError_t cudaStatus = cudaFree(devPtr);
    throwErrorMaybe(cudaStatus, "cudaFree failed!");
}

#include "CudaWithError.cuh"
#include<iostream>


CudaWithError::CudaWithError(string className): className(className) { }

void CudaWithError::throwErrorMaybe(cudaError_t cudaStatus, string error) {
    if (cudaStatus != cudaSuccess) {
        string totalError = className + ": " + error;
        cerr << endl << totalError;
        throw new runtime_error(totalError);
    }
}

void CudaWithError::setDevice(int device) {
	cudaError_t cudaStatus = cudaSetDevice(device);
    throwErrorMaybe(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
}

void CudaWithError::malloc(void** devPtr, size_t size) {

}

void CudaWithError::memcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind) {

}

void CudaWithError::deviceSynchronize() {

}

void CudaWithError::cudaFree(void* devPtr) {
    
}

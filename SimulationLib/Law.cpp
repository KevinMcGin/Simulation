#include "Law.h"

Law::Law(string className) {
	cudaWithError = new CudaWithError(className);
}
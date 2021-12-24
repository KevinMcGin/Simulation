#include "Law.h"

Law::Law(string className) {
	this-> className = className;
	cudaWithError = new CudaWithError(className);
}
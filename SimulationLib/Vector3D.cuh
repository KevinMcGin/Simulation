#pragma once
#include "cuda_runtime.h"

class Vector3D {
public:
	__device__ __host__ Vector3D(double x, double y, double z);
	__device__ __host__ Vector3D();
	double x,y,z;

	__device__ __host__ Vector3D unit();
	__device__ __host__ double magnitudeSquared();
	__device__ __host__ double magnitude();
	__device__ __host__ double dotProduct(Vector3D vec);
	__device__ __host__ Vector3D crossProduct(Vector3D vec);

	__device__ __host__ Vector3D operator+(const Vector3D& vec) const;
	__device__ __host__ Vector3D operator-(const Vector3D& vec) const;
	__device__ __host__ Vector3D operator*(const double scale) const;
	__device__ __host__ Vector3D operator/(const double scale) const;
	bool operator==(const Vector3D& vec) const;

	__device__ __host__ friend Vector3D operator*(const double scale, const Vector3D& vec);
};
#pragma once
#include "cuda_runtime.h"

class Vector3D {
public:
	__device__ __host__ Vector3D(double x, double y, double z);
	__device__ __host__ Vector3D();
	double x,y,z;

	Vector3D unit();
	double magnitudeSquared();
	double magnitude();
	double dotProduct(Vector3D vec);
	Vector3D crossProduct(Vector3D vec);

	__device__ __host__ Vector3D operator+(const Vector3D& vec) const;
	Vector3D operator-(const Vector3D& vec) const;
	Vector3D operator*(const double scale) const;
	Vector3D operator/(const double scale) const;
	bool operator==(const Vector3D& vec) const;

	friend Vector3D operator*(const double scale, const Vector3D& vec);
};
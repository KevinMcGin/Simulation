#pragma once
#include "cuda_runtime.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

template <typename T>
class Vector3D {
public:
	__device__ __host__ Vector3D<T>(T x, T y, T z) :
		x(x),
		y(y),
		z(z) { }
	__device__ __host__ Vector3D<T>() { }
	T x,y,z;

	__device__ __host__ Vector3D unit() {
		return Vector3D<T>(x,y,z) / magnitude();
	}
	__device__ __host__ T magnitudeSquared() {
		return x * x + y * y + z * z;
	}
	__device__ __host__ T magnitude() {
		return sqrt(magnitudeSquared());
	}
	__device__ __host__ T dotProduct(Vector3D<T> vec) {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	__device__ __host__ Vector3D<T> crossProduct(Vector3D vec) {
		return {y*vec.z - vec.y*z, -(x*vec.z - vec.x*z), x*vec.y - vec.x*y};
	} 

	__device__ __host__ Vector3D<T> operator+(const Vector3D<T>& vec) const {
		return {
			x + vec.x,
			y + vec.y,
			z + vec.z
		};
	}
	__device__ __host__ Vector3D<T> operator-(const Vector3D<T>& vec) const {
		return {
			x - vec.x,
			y - vec.y,
			z - vec.z
		};
	}
	__device__ __host__ Vector3D<T> operator*(const T scale) const {
		return {
			x * scale,
			y * scale,
			z * scale
		};
	}
	__device__ __host__ Vector3D<T> operator/(const T scale) const {
		return {
			x / scale,
			y / scale,
			z / scale
		};
	}

	__device__ __host__ friend Vector3D<T> operator*(const T scale, const Vector3D<T>& vec) {
		return vec * scale;
	}

	__device__ __host__ Vector3D<T> operator-() const {
		return Vector3D<T>(-x, -y, -z);
	}
	bool operator==(const Vector3D<T>& vec) const {
		return x == vec.x && y == vec.y && z == vec.z;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector3D<T>& vec) {
    	out << std::setprecision(17) << "{x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << "}";
    	return out;
	}
};
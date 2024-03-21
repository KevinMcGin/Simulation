#pragma once
#if defined(USE_GPU)
    #include "cuda_runtime.h"
#endif
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

template <typename T>
class Vector3D {
public:
#if defined(USE_GPU)
   __device__ __host__
#endif
inline Vector3D<T>(T x, T y, T z) :
		x(x),
		y(y),
		z(z) { }
#if defined(USE_GPU)
   __device__ __host__
#endif 
inline Vector3D<T>() { }
T x,y,z;

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D unit() {
		return Vector3D<T>(x,y,z) / magnitude();
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
T magnitudeSquared() {
		return x * x + y * y + z * z;
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
T magnitude() {
		return sqrt(magnitudeSquared());
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
T dotProduct(Vector3D<T> vec) {
		return x * vec.x + y * vec.y + z * vec.z;
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<T> crossProduct(Vector3D vec) {
		return {y*vec.z - vec.y*z, -(x*vec.z - vec.x*z), x*vec.y - vec.x*y};
	} 

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<T> operator+(const Vector3D<T>& vec) const {
		return {
			x + vec.x,
			y + vec.y,
			z + vec.z
		};
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<T> operator-(const Vector3D<T>& vec) const {
		return {
			x - vec.x,
			y - vec.y,
			z - vec.z
		};
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<T> operator*(const T scale) const {
		return {
			x * scale,
			y * scale,
			z * scale
		};
	}
#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<T> operator/(const T scale) const {
		return {
			x / scale,
			y / scale,
			z / scale
		};
	}

#if defined(USE_GPU)
   __device__ __host__
#endif 
friend Vector3D<T> operator*(const T scale, const Vector3D<T>& vec) {
		return vec * scale;
	}

#if defined(USE_GPU)
   __device__ __host__
#endif 
Vector3D<T> operator-() const {
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
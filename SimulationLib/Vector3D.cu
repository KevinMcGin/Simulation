#include "Vector3D.cuh"
#include <cmath>



__device__ __host__ Vector3D::Vector3D(double x, double y, double z):
	x(x),
	y(y),
	z(z)
{

}

__device__ __host__ Vector3D::Vector3D()
{

}
__device__ __host__
 Vector3D Vector3D::unit()
{
	return Vector3D(x,y,z) / this->magnitude();
}
__device__ __host__
 double Vector3D::magnitudeSquared()
{
	return x * x + y * y + z * z;
}
__device__ __host__
 double Vector3D::magnitude()
{
	return sqrt(this->magnitudeSquared());
}
__device__ __host__
double Vector3D::dotProduct(Vector3D vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}
__device__ __host__
Vector3D Vector3D::crossProduct(Vector3D vec) {
	return {y*vec.z - vec.y*z, -(x*vec.z - vec.x*z), x*vec.y - vec.x*y};
}

__device__ __host__ 
Vector3D Vector3D::operator+(const Vector3D& vec) const
{
	return {
		x + vec.x,
		y + vec.y,
		z + vec.z
	};
}
__device__ __host__
 Vector3D Vector3D::operator-(const Vector3D& vec) const
{
	return {
		x - vec.x,
		y - vec.y,
		z - vec.z
	};
}
__device__ __host__
 Vector3D Vector3D::operator*(const double scale) const
{
	return {
		x * scale,
		y * scale,
		z * scale
	};
}


__device__ __host__
 Vector3D Vector3D::operator/(const double scale) const
{
	return {
		x / scale,
		y / scale,
		z / scale
	};
}

bool Vector3D::operator==(const Vector3D& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}
__device__ __host__
Vector3D operator*(const double scale, const Vector3D& vec)
{
	return vec * scale;
}

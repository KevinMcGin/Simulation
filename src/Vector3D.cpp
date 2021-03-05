#include "Vector3D.h"



Vector3D Vector3D::operator+(const Vector3D& vec) const
{
	return {
		x + vec.x,
		y + vec.y,
		z + vec.z
	};
}

Vector3D Vector3D::operator-(const Vector3D& vec) const
{
	return {
		x - vec.x,
		y - vec.y,
		z - vec.z
	};
}

Vector3D Vector3D::operator*(const double scale) const
{
	return {
		x * scale,
		y * scale,
		z * scale
	};
}

Vector3D Vector3D::operator/(const double scale) const
{
	return {
		x / scale,
		y / scale,
		z / scale
	};
}

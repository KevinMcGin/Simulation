#include "Vector3D.h"
#include <cmath>



Vector3D::Vector3D(double x, double y, double z):
	x(x),
	y(y),
	z(z)
{

}

Vector3D::Vector3D()
{

}

Vector3D Vector3D::unit()
{
	return Vector3D(x,y,z) / sqrt(this->magnitudeSquared());
}

double Vector3D::magnitudeSquared()
{
	return x * x + y * y + z * z;
}

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

bool Vector3D::operator==(const Vector3D& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

Vector3D operator*(const double scale, const Vector3D& vec)
{
	return vec * scale;
}

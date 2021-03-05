#pragma once

class Vector3D {
public:
	double x,y,z;

	Vector3D operator+(const Vector3D& vec) const;

	Vector3D operator-(const Vector3D& vec) const;

	Vector3D operator*(const double scale) const;

	friend Vector3D operator* (const double scale, const Vector3D& vec)
	{
		return vec * scale;
	}

	Vector3D operator/(const double scale) const;
};
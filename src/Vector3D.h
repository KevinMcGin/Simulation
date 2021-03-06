#pragma once

class Vector3D {
public:
	Vector3D(double x, double y, double z);
	Vector3D();
	double x,y,z;

	Vector3D unit();
	double magnitudeSquared();

	Vector3D operator+(const Vector3D& vec) const;

	Vector3D operator-(const Vector3D& vec) const;

	Vector3D operator*(const double scale) const;

	friend Vector3D operator* (const double scale, const Vector3D& vec)
	{
		return vec * scale;
	}

	Vector3D operator/(const double scale) const;
};
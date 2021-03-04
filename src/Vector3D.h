#pragma once

class Vector3D {
public:
	double x,y,z;

	Vector3D operator+ (Vector3D const& obj) {
		return {
			x + obj.x,
			y + obj.y,
			z + obj.z
		};
	}

	Vector3D operator- (Vector3D const& obj) {
		return {
			x - obj.x,
			y - obj.y,
			z - obj.z
		};
	}
};
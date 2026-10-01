#include  "gtest/gtest.h"
#include "shared/particle/model/Vector3D.cuh"
#include <cmath>
#include <sstream>

TEST(Vector3DTest, vectorsMagnitudeSquared) {
	Vector3D<Real> v1({ (Real)(-1/sqrt(2)), (Real)(1/sqrt(2)), 0.0 });
	Real magnitudeSquared = v1.magnitudeSquared();
	EXPECT_DOUBLE_EQ(1, magnitudeSquared);
}

TEST(Vector3DTest, vectorsMagnitude) {
	Vector3D<Real> v1({ -1.0 / (Real)(sqrt(2)), (Real)(1 / sqrt(2)), 0.0 });
	Real magnitudeSquared = v1.magnitude();
	EXPECT_DOUBLE_EQ(1, magnitudeSquared);
}

TEST(Vector3DTest, vectorsUnit) {
	Vector3D<Real> v1({ 0,-1,1 });
	Vector3D<Real> vUnit = v1.unit();
	EXPECT_EQ(Vector3D<Real>(0, -1 / sqrt(2) , 1 / sqrt(2)), vUnit);
}

TEST(Vector3DTest, vectorsDot) {
	Vector3D<Real> v1({ 3,1,2 });
	Vector3D<Real> v2({ -0.5,0,2 });
	Real dotProduct = v1.dotProduct(v2);
	EXPECT_DOUBLE_EQ(2.5, dotProduct);
}

TEST(Vector3DTest, vectorsDotPerpendicular) {
	Vector3D<Real> v1({ 0,1,0 });
	Vector3D<Real> v2({ -1,0,2 });
	Real dotProduct = v1.dotProduct(v2);
	EXPECT_DOUBLE_EQ(0, dotProduct);
}

TEST(Vector3DTest, vectorsCross1) {
	Vector3D<Real> v1({ 0,2,1 });
	Vector3D<Real> v2({ 1,-1,3 });
	Vector3D<Real> crossProduct = v1.crossProduct(v2);
	EXPECT_EQ(Vector3D<Real>(7,1,-2), crossProduct);
}

TEST(Vector3DTest, vectorsCross2) {
	Vector3D<Real> v1({ 0, 0, 1 });
	Vector3D<Real> v2({ 1,0,0 });
	Vector3D<Real> crossProduct = v1.crossProduct(v2);
	EXPECT_EQ(Vector3D<Real>(0,1,0), crossProduct);
}

TEST(Vector3DTest, vectorsAdd) {
	Vector3D<Real> v1({ 0,1,0 });
	Vector3D<Real> v2({ -1,0,0 });
	Vector3D<Real> v3 = v1 + v2;
	EXPECT_EQ(Vector3D<Real>(-1, 1, 0), v3);
}

TEST(Vector3DTest, vectorsSubtract) {
	Vector3D<Real> v1({ 0,1,0 });
	Vector3D<Real> v2({ -1,0,2 });
	Vector3D<Real> v3 = v1 - v2;
	EXPECT_EQ(Vector3D<Real>(1, 1, -2), v3);
}

TEST(Vector3DTest, vectorsMultiply) {
	Vector3D<Real> v1({ 0,1,-1 });
	Vector3D<Real> v2 = 3.0 * v1;
	EXPECT_EQ(Vector3D<Real>(0, 3, -3), v2);
}

TEST(Vector3DTest, vectorsDivide) {
	Vector3D<Real> v1({ 0,1,-1 });
	Vector3D<Real> v2 = v1 / 2.0;
	EXPECT_EQ(Vector3D<Real>(0, 0.5, -0.5), v2);
}

TEST(Vector3DTest, vectorsPrint) {
	Vector3D<Real> v1( 0,1,-1 );
	std::ostringstream vectorStream;
    vectorStream << v1;
    std::string vectorString = vectorStream.str();
	EXPECT_EQ("{x: 0, y: 1, z: -1}", vectorString);
}
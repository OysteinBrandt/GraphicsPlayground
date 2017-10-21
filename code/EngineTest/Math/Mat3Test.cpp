#include <gtest/gtest.h>

#include "Math/Mat3.h"
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Math/Constants.h"
#include "MathTestHelper.h"

using math::Mat3;
using math::Vec3;
using math::Vec2;

TEST(Mat3, Constructor)
{
	Mat3 defaultMatrix;
	EXPECT_FLOAT_EQ(1.f, defaultMatrix.x1);
	EXPECT_FLOAT_EQ(0.f, defaultMatrix.y1);
	EXPECT_FLOAT_EQ(0.f, defaultMatrix.z1);
	EXPECT_FLOAT_EQ(0.f, defaultMatrix.x2);
	EXPECT_FLOAT_EQ(1.f, defaultMatrix.y2);
	EXPECT_FLOAT_EQ(0.f, defaultMatrix.z2);
	EXPECT_FLOAT_EQ(0.f, defaultMatrix.x3);
	EXPECT_FLOAT_EQ(0.f, defaultMatrix.y3);
	EXPECT_FLOAT_EQ(1.f, defaultMatrix.z3);

	Mat3 customMatrix(2.5f, 1.0f, 2.0f,
										1.2f, 3.4f, 5.0f,
										0.1f, 2.5f, 23.0f);

	EXPECT_FLOAT_EQ(2.5f, customMatrix.x1);
	EXPECT_FLOAT_EQ(1.0f, customMatrix.y1);
	EXPECT_FLOAT_EQ(2.0f, customMatrix.z1);
	EXPECT_FLOAT_EQ(1.2f, customMatrix.x2);
	EXPECT_FLOAT_EQ(3.4f, customMatrix.y2);
	EXPECT_FLOAT_EQ(5.0f, customMatrix.z2);
	EXPECT_FLOAT_EQ(0.1f, customMatrix.x3);
	EXPECT_FLOAT_EQ(2.5f, customMatrix.y3);
	EXPECT_FLOAT_EQ(23.f, customMatrix.z3);
}

TEST(Mat3, MatrixVectorMultiply)
{
	Vec3 result1 = Mat3{} * Vec3{ 1.0f, 1.0f, 1.0f };
	EXPECT_FLOAT_EQ(1.0f, result1.x);
	EXPECT_FLOAT_EQ(1.0f, result1.y);
	EXPECT_FLOAT_EQ(1.0f, result1.z);

	Mat3 matrix{ 1, 2, 3,
							 4, 5, 6,
							 7, 8, 9 };
	Vec3 vector{ 1, 2, 3 };
	Vec3 result2 = matrix * vector;
	EXPECT_FLOAT_EQ(14.0f, result2.x);
	EXPECT_FLOAT_EQ(32.0f, result2.y);
	EXPECT_FLOAT_EQ(50.0f, result2.z);
}

TEST(Mat3, Rotate)
{
	Mat3 rot;
	rot = Mat3::rotate(0, Mat3::Axis::Z);
	EXPECT_FLOAT_EQ(1, rot.x1);
	EXPECT_FLOAT_EQ(0, rot.y1);
	EXPECT_FLOAT_EQ(0, rot.z1);
	EXPECT_FLOAT_EQ(0, rot.x2);
	EXPECT_FLOAT_EQ(1, rot.y2);
	EXPECT_FLOAT_EQ(0, rot.z2);
	EXPECT_FLOAT_EQ(0, rot.x3);
	EXPECT_FLOAT_EQ(0, rot.y3);
	EXPECT_FLOAT_EQ(1, rot.z3);

	rot = Mat3::rotate(math::PI, Mat3::Axis::Z);
	EXPECT_FLOAT_EQ(-1, rot.x1);
	EXPECT_TRUE(closeEnough(0.f, rot.y1));
	EXPECT_FLOAT_EQ(0, rot.z1);
	EXPECT_TRUE(closeEnough(0.f, rot.x2));
	EXPECT_FLOAT_EQ(-1, rot.y2);
	EXPECT_FLOAT_EQ(0, rot.z2);
	EXPECT_FLOAT_EQ(0, rot.x3);
	EXPECT_FLOAT_EQ(0, rot.y3);
	EXPECT_FLOAT_EQ(1, rot.z3);

	rot = Mat3::rotate(math::PI / 2.f, Mat3::Axis::Z);
	EXPECT_TRUE(closeEnough(0.f, rot.x1));
	EXPECT_FLOAT_EQ(-1, rot.y1);
	EXPECT_FLOAT_EQ(0, rot.z1);
	EXPECT_FLOAT_EQ(1, rot.x2);
	EXPECT_TRUE(closeEnough(0.f, rot.y2));
	EXPECT_FLOAT_EQ(0, rot.z2);
	EXPECT_FLOAT_EQ(0, rot.x3);
	EXPECT_FLOAT_EQ(0, rot.y3);
	EXPECT_FLOAT_EQ(1, rot.z3);
}

TEST(Mat3, Translate)
{
	auto transformation = Mat3::translate(Vec2(4, 8));
	EXPECT_FLOAT_EQ(1, transformation.x1);
	EXPECT_FLOAT_EQ(0, transformation.y1);
	EXPECT_FLOAT_EQ(4, transformation.z1);

	EXPECT_FLOAT_EQ(0, transformation.x2);
	EXPECT_FLOAT_EQ(1, transformation.y2);
	EXPECT_FLOAT_EQ(8, transformation.z2);

	EXPECT_FLOAT_EQ(0, transformation.x3);
	EXPECT_FLOAT_EQ(0, transformation.y3);
	EXPECT_FLOAT_EQ(1, transformation.z3);

	Vec3 vector{ -3, 8 , 1 };
	auto result = transformation * vector;
	EXPECT_FLOAT_EQ(1, result.x);
	EXPECT_FLOAT_EQ(16, result.y);
	EXPECT_FLOAT_EQ(1, result.z);
}

TEST(Mat3, MatrixMatrixMultiply)
{
	Mat3 matrix{ 1, 2, 3, 
							 4, 5, 6, 
							 7, 8, 9 };
	auto result = matrix * matrix;
	EXPECT_FLOAT_EQ(30.f, result.x1);
	EXPECT_FLOAT_EQ(36.f, result.y1);
	EXPECT_FLOAT_EQ(42.f, result.z1);

	EXPECT_FLOAT_EQ(66.f, result.x2);
	EXPECT_FLOAT_EQ(81.f, result.y2);
	EXPECT_FLOAT_EQ(96.f, result.z2);

	EXPECT_FLOAT_EQ(102.f, result.x3);
	EXPECT_FLOAT_EQ(126.f, result.y3);
	EXPECT_FLOAT_EQ(150.f, result.z3);
}
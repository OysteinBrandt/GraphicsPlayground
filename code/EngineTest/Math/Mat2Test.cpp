#include <gtest/gtest.h>

#include "Engine/Math/Mat2.h"
#include "Engine/Math/Vec2.h"
#include "MathTestHelper.h"
#include "Engine/Math/Constants.h"

using math::Mat2;
using math::Vec2;

TEST(Mat2, Constructor)
{
	Mat2 identity;
	EXPECT_FLOAT_EQ(1.f, identity.x1);
	EXPECT_FLOAT_EQ(0.f, identity.y1);
	EXPECT_FLOAT_EQ(0.f, identity.x2);
	EXPECT_FLOAT_EQ(1.f, identity.y2);

	Mat2 matrix{ 2.f, 3.0f, 4.0f, 5.0f };
	EXPECT_FLOAT_EQ(2.f, matrix.x1);
	EXPECT_FLOAT_EQ(3.f, matrix.y1);
	EXPECT_FLOAT_EQ(4.f, matrix.x2);
	EXPECT_FLOAT_EQ(5.f, matrix.y2);
}

TEST(Mat2, MatrixVectorMultiply)
{
	Vec2 result1 = Mat2{} * Vec2{ 1.0f, 1.0f };
	EXPECT_FLOAT_EQ(result1.x, 1.0f);
	EXPECT_FLOAT_EQ(result1.y, 1.0f);

	Mat2 matrix{ 2, -3,
							 4, -5 };
	Vec2 vector{3, 9};
	Vec2 result2 = matrix * vector;
	EXPECT_FLOAT_EQ(result2.x, -21.0f);
	EXPECT_FLOAT_EQ(result2.y, -33.0f);
}

TEST(Mat2, Rotate)
{
	Mat2 op;
	op = Mat2::rotate(0.f);
	EXPECT_FLOAT_EQ(op.x1, 1);
	EXPECT_FLOAT_EQ(op.y1, 0);
	EXPECT_FLOAT_EQ(op.x2, 0);
	EXPECT_FLOAT_EQ(op.y2, 1);

	op = Mat2::rotate(math::PI);
	EXPECT_FLOAT_EQ(op.x1, -1);
	EXPECT_TRUE(closeEnough(op.y1, 0.f));
	EXPECT_TRUE(closeEnough(op.x2, 0.f));
	EXPECT_FLOAT_EQ(op.y2, -1);

	op = Mat2::rotate(math::PI / 2.f);
	EXPECT_TRUE(closeEnough(op.x1, 0.f));
	EXPECT_FLOAT_EQ(op.y1, -1);
	EXPECT_FLOAT_EQ(op.x2, 1);
	EXPECT_TRUE(closeEnough(op.y2, 0.f));

	op = Mat2::rotate(math::PI / 4.f);
	const float sqrt2over2 = std::sqrt(2.f) / 2.f;
	EXPECT_FLOAT_EQ(op.x1, sqrt2over2);
	EXPECT_FLOAT_EQ(op.y1, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.x2, sqrt2over2);
	EXPECT_FLOAT_EQ(op.y2, sqrt2over2);

	op = Mat2::rotate(-math::PI / 4.f);
	EXPECT_FLOAT_EQ(op.x1, sqrt2over2);
	EXPECT_FLOAT_EQ(op.y1, sqrt2over2);
	EXPECT_FLOAT_EQ(op.x2, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.y2, sqrt2over2);

	op = Mat2::rotate(math::PI / 3.f);
	const float sqrt3over2 = std::sqrt(3.f) / 2.f;
	EXPECT_FLOAT_EQ(op.x1, .5);
	EXPECT_FLOAT_EQ(op.y1, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.x2, sqrt3over2);
	EXPECT_FLOAT_EQ(op.y2, .5);

	op = Mat2::rotate(-math::PI / 3.f);
	EXPECT_FLOAT_EQ(op.x1, .5);
	EXPECT_FLOAT_EQ(op.y1, sqrt3over2);
	EXPECT_FLOAT_EQ(op.x2, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.y2, .5);

	// TODO (obr): Also support rotating a defined matrix variable?
	/*
		Mat2 matrix;
		matrix.rotate(1.57079633f);  // 90 degrees
		EXPECT_FLOAT_EQ(matrix.x1, 0);
		EXPECT_FLOAT_EQ(matrix.y1, -1);
		EXPECT_FLOAT_EQ(matrix.x2, 1);
		EXPECT_FLOAT_EQ(matrix.y2, 0);
	*/
}
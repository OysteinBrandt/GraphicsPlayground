#include <gtest/gtest.h>

#include <Math/Mat4.h>
#include <Math/Vec3.h>
#include <Math/Constants.h>
#include "MathTestHelper.h"

using math::Mat4;
using math::Vec3;

TEST(Mat4, Constructor)
{
	Mat4 m;
	EXPECT_FLOAT_EQ(1.0f, m.x[0]);
	EXPECT_FLOAT_EQ(0.0f, m.x[1]);
	EXPECT_FLOAT_EQ(0.0f, m.x[2]);
	EXPECT_FLOAT_EQ(0.0f, m.x[3]);

	EXPECT_FLOAT_EQ(0.0f, m.y[0]);
	EXPECT_FLOAT_EQ(1.0f, m.y[1]);
	EXPECT_FLOAT_EQ(0.0f, m.y[2]);
	EXPECT_FLOAT_EQ(0.0f, m.y[3]);

	EXPECT_FLOAT_EQ(0.0f, m.z[0]);
	EXPECT_FLOAT_EQ(0.0f, m.z[1]);
	EXPECT_FLOAT_EQ(1.0f, m.z[2]);
	EXPECT_FLOAT_EQ(0.0f, m.z[3]);

	EXPECT_FLOAT_EQ(0.0f, m.w[0]);
	EXPECT_FLOAT_EQ(0.0f, m.w[1]);
	EXPECT_FLOAT_EQ(0.0f, m.w[2]);
	EXPECT_FLOAT_EQ(1.0f, m.w[3]);

	m = Mat4{ 3.4f, 1.2f, 2.2f, 3.0f,
					  1.2f, 3.4f, 5.6f, 7.0f,
 						 9.f, 1.2f, 5.0f, 3.0f,
					 12.0f, 1.0f, 2.2f, 3.1f };

	  EXPECT_FLOAT_EQ(3.4f,  m.x[0]);
		EXPECT_FLOAT_EQ(1.2f,  m.y[0]);
		EXPECT_FLOAT_EQ(2.2f,  m.z[0]);
		EXPECT_FLOAT_EQ(3.0f,  m.w[0]);
		EXPECT_FLOAT_EQ(1.2f,  m.x[1]);
		EXPECT_FLOAT_EQ(3.4f,  m.y[1]);
		EXPECT_FLOAT_EQ(5.6f,  m.z[1]);
		EXPECT_FLOAT_EQ(7.0f,  m.w[1]);
		EXPECT_FLOAT_EQ(9.f,   m.x[2]);
		EXPECT_FLOAT_EQ(1.2f,  m.y[2]);
		EXPECT_FLOAT_EQ(5.0f,  m.z[2]);
		EXPECT_FLOAT_EQ(3.0f,  m.w[2]);
	  EXPECT_FLOAT_EQ(12.0f, m.x[3]);
		EXPECT_FLOAT_EQ(1.0f,  m.y[3]);
		EXPECT_FLOAT_EQ(2.2f,  m.z[3]);
		EXPECT_FLOAT_EQ(3.1f,  m.w[3]);
}

TEST(Mat4, MatrixVectorMultiply)
{
	Vec3 res = Mat4{} * Vec3{ 1.0f, 1.0f, 1.0f };
	EXPECT_FLOAT_EQ(1.0f, res.x);
	EXPECT_FLOAT_EQ(1.0f, res.y);
	EXPECT_FLOAT_EQ(1.0f, res.z);

	Mat4 matrix{ 1, 2, 3, 4,
							 5, 6, 7, 8,
							 9, 10, 11, 12,
							13, 14, 15, 16 };
	Vec3 vector{ 1, 2, 3 };
	res = matrix * vector;
	EXPECT_FLOAT_EQ(18.0f, res.x);
	EXPECT_FLOAT_EQ(46.0f, res.y);
	EXPECT_FLOAT_EQ(74.0f, res.z);

}

TEST(Mat4, RotateFixedAxis)
{
	Mat4 rot = Mat4::rotate(0, Mat4::Axis::Z);
	EXPECT_FLOAT_EQ(1.0f, rot.x[0]);
	EXPECT_FLOAT_EQ(0.0f, rot.x[1]);
	EXPECT_FLOAT_EQ(0.0f, rot.x[2]);
	EXPECT_FLOAT_EQ(0.0f, rot.x[3]);

	EXPECT_FLOAT_EQ(0.0f, rot.y[0]);
	EXPECT_FLOAT_EQ(1.0f, rot.y[1]);
	EXPECT_FLOAT_EQ(0.0f, rot.y[2]);
	EXPECT_FLOAT_EQ(0.0f, rot.y[3]);

	EXPECT_FLOAT_EQ(0.0f, rot.z[0]);
	EXPECT_FLOAT_EQ(0.0f, rot.z[1]);
	EXPECT_FLOAT_EQ(1.0f, rot.z[2]);
	EXPECT_FLOAT_EQ(0.0f, rot.z[3]);

	EXPECT_FLOAT_EQ(0.0f, rot.w[0]);
	EXPECT_FLOAT_EQ(0.0f, rot.w[1]);
	EXPECT_FLOAT_EQ(0.0f, rot.w[2]);
	EXPECT_FLOAT_EQ(1.0f, rot.w[3]);

	rot = Mat4::rotate(math::PI, Mat4::Axis::X);
	EXPECT_FLOAT_EQ(1,           rot.x[0]);
	EXPECT_FLOAT_EQ(0,				   rot.y[0]);
	EXPECT_FLOAT_EQ(0,           rot.z[0]);
	EXPECT_FLOAT_EQ(0,           rot.w[0]);
	EXPECT_FLOAT_EQ(0,				   rot.x[1]);
	EXPECT_FLOAT_EQ(-1,          rot.y[1]);
	EXPECT_TRUE(closeEnough(0.f, rot.z[1]));
	EXPECT_FLOAT_EQ(0,           rot.w[1]);
	EXPECT_FLOAT_EQ(0,           rot.x[2]);
	EXPECT_TRUE(closeEnough(0.f, rot.y[2]));
	EXPECT_FLOAT_EQ(-1,          rot.z[2]);
	EXPECT_FLOAT_EQ(0,           rot.w[2]);
	EXPECT_FLOAT_EQ(0,           rot.x[3]);
	EXPECT_FLOAT_EQ(0,           rot.y[3]);
	EXPECT_FLOAT_EQ(0,           rot.z[3]);
	EXPECT_FLOAT_EQ(1,           rot.w[3]);

	rot = Mat4::rotate(math::PI, Mat4::Axis::Y);
	EXPECT_FLOAT_EQ(-1, rot.x[0]);
	EXPECT_FLOAT_EQ(0, rot.y[0]);
	EXPECT_TRUE(closeEnough(0.f, rot.z[0]));
	EXPECT_FLOAT_EQ(0, rot.w[0]);
	EXPECT_FLOAT_EQ(0, rot.x[1]);
	EXPECT_FLOAT_EQ(1, rot.y[1]);
	EXPECT_FLOAT_EQ(0, rot.z[1]);
	EXPECT_FLOAT_EQ(0, rot.w[1]);
	EXPECT_TRUE(closeEnough(0.f, rot.x[2]));
	EXPECT_FLOAT_EQ(0, rot.y[2]);
	EXPECT_FLOAT_EQ(-1, rot.z[2]);
	EXPECT_FLOAT_EQ(0, rot.w[2]);
	EXPECT_FLOAT_EQ(0, rot.x[3]);
	EXPECT_FLOAT_EQ(0, rot.y[3]);
	EXPECT_FLOAT_EQ(0, rot.z[3]);
	EXPECT_FLOAT_EQ(1, rot.w[3]);

	rot = Mat4::rotate(math::PI, Mat4::Axis::Z);
	EXPECT_FLOAT_EQ(-1,          rot.x[0]);
	EXPECT_TRUE(closeEnough(0.f, rot.y[0]));
	EXPECT_FLOAT_EQ(0,           rot.z[0]);
	EXPECT_FLOAT_EQ(0,           rot.w[0]);
	EXPECT_TRUE(closeEnough(0.f, rot.x[1]));
	EXPECT_FLOAT_EQ(-1,          rot.y[1]);
	EXPECT_FLOAT_EQ(0,           rot.z[1]);
	EXPECT_FLOAT_EQ(0,           rot.w[1]);
	EXPECT_FLOAT_EQ(0,           rot.x[2]);
	EXPECT_FLOAT_EQ(0,           rot.y[2]);
	EXPECT_FLOAT_EQ(1,           rot.z[2]);
	EXPECT_FLOAT_EQ(0,           rot.w[2]);
	EXPECT_FLOAT_EQ(0,           rot.x[3]);
	EXPECT_FLOAT_EQ(0,           rot.y[3]);
	EXPECT_FLOAT_EQ(0,           rot.z[3]);
	EXPECT_FLOAT_EQ(1,           rot.w[3]);
}

TEST(Mat4, RotateAnyAxis)
{
	auto rot = Mat4::rotate(math::PI, {1.0f, 0.0f, 0.0f});
	EXPECT_FLOAT_EQ(1, rot.x[0]);
	EXPECT_FLOAT_EQ(0, rot.y[0]);
	EXPECT_FLOAT_EQ(0, rot.z[0]);
	EXPECT_FLOAT_EQ(0, rot.w[0]);
	EXPECT_FLOAT_EQ(0, rot.x[1]);
	EXPECT_FLOAT_EQ(-1, rot.y[1]);
	EXPECT_TRUE(closeEnough(0.f, rot.z[1]));
	EXPECT_FLOAT_EQ(0, rot.w[1]);
	EXPECT_FLOAT_EQ(0, rot.x[2]);
	EXPECT_TRUE(closeEnough(0.f, rot.y[2]));
	EXPECT_FLOAT_EQ(-1, rot.z[2]);
	EXPECT_FLOAT_EQ(0, rot.w[2]);
	EXPECT_FLOAT_EQ(0, rot.x[3]);
	EXPECT_FLOAT_EQ(0, rot.y[3]);
	EXPECT_FLOAT_EQ(0, rot.z[3]);
	EXPECT_FLOAT_EQ(1, rot.w[3]);

	// TODO: Rotate around other angles eg. {0.5f, 0.5f, 0.0f}
}

TEST(Mat4, TranslateXYZ)
{
	auto m = Mat4::translate(4, 8, 3);
	EXPECT_FLOAT_EQ(1.0f, m.x[0]);
	EXPECT_FLOAT_EQ(0.0f, m.x[1]);
	EXPECT_FLOAT_EQ(0.0f, m.x[2]);
	EXPECT_FLOAT_EQ(0.0f, m.x[3]);

	EXPECT_FLOAT_EQ(0.0f, m.y[0]);
	EXPECT_FLOAT_EQ(1.0f, m.y[1]);
	EXPECT_FLOAT_EQ(0.0f, m.y[2]);
	EXPECT_FLOAT_EQ(0.0f, m.y[3]);

	EXPECT_FLOAT_EQ(0.0f, m.z[0]);
	EXPECT_FLOAT_EQ(0.0f, m.z[1]);
	EXPECT_FLOAT_EQ(1.0f, m.z[2]);
	EXPECT_FLOAT_EQ(0.0f, m.z[3]);

	EXPECT_FLOAT_EQ(4.0f, m.w[0]);
	EXPECT_FLOAT_EQ(8.0f, m.w[1]);
	EXPECT_FLOAT_EQ(3.0f, m.w[2]);
	EXPECT_FLOAT_EQ(1.0f, m.w[3]);
}

TEST(Mat4, TranslateVec3)
{
	auto m = Mat4::translate(Vec3{ 2, 3, 4 });
	EXPECT_FLOAT_EQ(1.0f, m.x[0]);
	EXPECT_FLOAT_EQ(0.0f, m.x[1]);
	EXPECT_FLOAT_EQ(0.0f, m.x[2]);
	EXPECT_FLOAT_EQ(0.0f, m.x[3]);

	EXPECT_FLOAT_EQ(0.0f, m.y[0]);
	EXPECT_FLOAT_EQ(1.0f, m.y[1]);
	EXPECT_FLOAT_EQ(0.0f, m.y[2]);
	EXPECT_FLOAT_EQ(0.0f, m.y[3]);

	EXPECT_FLOAT_EQ(0.0f, m.z[0]);
	EXPECT_FLOAT_EQ(0.0f, m.z[1]);
	EXPECT_FLOAT_EQ(1.0f, m.z[2]);
	EXPECT_FLOAT_EQ(0.0f, m.z[3]);

	EXPECT_FLOAT_EQ(2.0f, m.w[0]);
	EXPECT_FLOAT_EQ(3.0f, m.w[1]);
	EXPECT_FLOAT_EQ(4.0f, m.w[2]);
	EXPECT_FLOAT_EQ(1.0f, m.w[3]);

	Vec3 vec{ -4, 6, 2 };
	auto res = m * vec;
	EXPECT_FLOAT_EQ(-2.0f, res.x);
	EXPECT_FLOAT_EQ(9.f, res.y);
	EXPECT_FLOAT_EQ(6.0f, res.z);
}

TEST(Mat4, MatrixMatrixMultiply)
{
	Mat4 m{ 1, 2, 3, 4,
					5, 6, 7, 8,
					9, 1, 2, 3,
					4, 5, 6, 7 };
	auto res = m * m;
	EXPECT_FLOAT_EQ(54.f, res.x[0]);
	EXPECT_FLOAT_EQ(130.f, res.x[1]);
	EXPECT_FLOAT_EQ(44.f, res.x[2]);
	EXPECT_FLOAT_EQ(111.f, res.x[3]);

	EXPECT_FLOAT_EQ(37.f, res.y[0]);
	EXPECT_FLOAT_EQ(93.f, res.y[1]);
	EXPECT_FLOAT_EQ(41.f, res.y[2]);
	EXPECT_FLOAT_EQ(79.f, res.y[3]);

	EXPECT_FLOAT_EQ(47.f, res.z[0]);
	EXPECT_FLOAT_EQ(119.f, res.z[1]);
	EXPECT_FLOAT_EQ(56.f, res.z[2]);
	EXPECT_FLOAT_EQ(101.f, res.z[3]);

	EXPECT_FLOAT_EQ(57.f, res.w[0]);
	EXPECT_FLOAT_EQ(145.f, res.w[1]);
	EXPECT_FLOAT_EQ(71.f, res.w[2]);
	EXPECT_FLOAT_EQ(123.f, res.w[3]);
}

TEST(Mat4, Scale)
{
	auto m = Mat4::scale(-2.f, 0.5f, 10.f);
	EXPECT_FLOAT_EQ(-2.0f, m.x[0]);
	EXPECT_FLOAT_EQ(0.0f, m.x[1]);
	EXPECT_FLOAT_EQ(0.0f, m.x[2]);
	EXPECT_FLOAT_EQ(0.0f, m.x[3]);

	EXPECT_FLOAT_EQ(0.0f, m.y[0]);
	EXPECT_FLOAT_EQ(0.5f, m.y[1]);
	EXPECT_FLOAT_EQ(0.0f, m.y[2]);
	EXPECT_FLOAT_EQ(0.0f, m.y[3]);

	EXPECT_FLOAT_EQ(0.0f, m.z[0]);
	EXPECT_FLOAT_EQ(0.0f, m.z[1]);
	EXPECT_FLOAT_EQ(10.0f, m.z[2]);
	EXPECT_FLOAT_EQ(0.0f, m.z[3]);

	EXPECT_FLOAT_EQ(0.0f, m.w[0]);
	EXPECT_FLOAT_EQ(0.0f, m.w[1]);
	EXPECT_FLOAT_EQ(0.0f, m.w[2]);
	EXPECT_FLOAT_EQ(1.0f, m.w[3]);
}
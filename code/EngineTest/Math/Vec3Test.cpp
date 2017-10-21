#include <gtest/gtest.h>

#include <Math/Vec3.h>

using math::Vec3;

TEST(Vec3, Constructor)
{
	Vec3 defaultConstructor;
	EXPECT_FLOAT_EQ(0.f, defaultConstructor.x);
	EXPECT_FLOAT_EQ(0.f, defaultConstructor.y);
	EXPECT_FLOAT_EQ(0.f, defaultConstructor.z);

	Vec3 first(0.f, 1.f, 2.f);
	EXPECT_FLOAT_EQ(0.f, first.x);
	EXPECT_FLOAT_EQ(1.f, first.y);
	EXPECT_FLOAT_EQ(2.f, first.z);

	Vec3 second(-0.f, -1.f, -2.f);
	EXPECT_FLOAT_EQ(-0.f, second.x);
	EXPECT_FLOAT_EQ(-1.f, second.y);
	EXPECT_FLOAT_EQ(-2.f, second.z);
}

TEST(Vec3, VectorAddition)
{
	Vec3 first(0.f, 1.f, 2.f);
	Vec3 second(3.f, 4.f, 5.f);
	Vec3 result = first + second;
	EXPECT_FLOAT_EQ(3.f, result.x);
	EXPECT_FLOAT_EQ(5.f, result.y);
	EXPECT_FLOAT_EQ(7.f, result.z);

	Vec3 third(-0.f, -1.f, 2.f);
	Vec3 fourth(3.f, -4.f, -5.f);
	Vec3 result2 = third + fourth;
	EXPECT_FLOAT_EQ(3.f, result2.x);
	EXPECT_FLOAT_EQ(-5.f, result2.y);
	EXPECT_FLOAT_EQ(-3.f, result2.z);

	Vec3 result3 = first + second + third + fourth;
	EXPECT_FLOAT_EQ(6.f,  result3.x);
	EXPECT_FLOAT_EQ(0.f, result3.y);
	EXPECT_FLOAT_EQ(4.f, result3.z);
}

TEST(Vec3, VectorAdditionAssignment)
{
	Vec3 result(0.f, 1.f, 2.f);
	Vec3 first(3.f, 4.f, 5.f);
	result += first;
	EXPECT_FLOAT_EQ(3.f, result.x);
	EXPECT_FLOAT_EQ(5.f, result.y);
	EXPECT_FLOAT_EQ(7.f, result.z);

	Vec3 result2(0.f, -1.f, 2.f);
	Vec3 second(3.f, -4.f, -5.f);
	result2 += second;
	EXPECT_FLOAT_EQ(3.f, result2.x);
	EXPECT_FLOAT_EQ(-5.f, result2.y);
	EXPECT_FLOAT_EQ(-3.f, result2.z);
}

TEST(Vec3, VectorSubtraction)
{
	Vec3 first(0.f, 1.f, 2.f);
	Vec3 second(3.f, 4.f, 5.f);
	Vec3 result = first - second;
	EXPECT_FLOAT_EQ(-3.f, result.x);
	EXPECT_FLOAT_EQ(-3.f, result.y);
	EXPECT_FLOAT_EQ(-3.f, result.z);

	Vec3 third(-0.f, -1.f, 2.f);
	Vec3 fourth(3.f, -4.f, -5.f);
	Vec3 result2 = third - fourth;
	EXPECT_FLOAT_EQ(-3.f, result2.x);
	EXPECT_FLOAT_EQ(3.f, result2.y);
	EXPECT_FLOAT_EQ(7.f, result2.z);
}

TEST(Vec3, VectorSubtractionAssignment)
{
	Vec3 result(0.f, 1.f, 2.f);
	Vec3 first(3.f, 4.f, 5.f);
	result -= first;
	EXPECT_FLOAT_EQ(-3.f, result.x);
	EXPECT_FLOAT_EQ(-3.f, result.y);
	EXPECT_FLOAT_EQ(-3.f, result.z);

	Vec3 result2(0.f, -1.f, 2.f);
	Vec3 second(3.f, -4.f, -5.f);
	result2 -= second;
	EXPECT_FLOAT_EQ(-3.f, result2.x);
	EXPECT_FLOAT_EQ(3.f, result2.y);
	EXPECT_FLOAT_EQ(7.f, result2.z);
}

TEST(Vec3, ScalarMultiplication)
{
	Vec3 first(1.0f, 2.f, 3.f);
	Vec3 result1 = 2 * first;
	EXPECT_FLOAT_EQ(2.f, result1.x);
	EXPECT_FLOAT_EQ(4.f, result1.y);
	EXPECT_FLOAT_EQ(6.f, result1.z);

	Vec3 result2 = first * (-3);
	EXPECT_FLOAT_EQ(-3.f, result2.x);
	EXPECT_FLOAT_EQ(-6.f, result2.y);
	EXPECT_FLOAT_EQ(-9.f, result2.z);
}

TEST(Vec3, ScalarMultiplicationAssignment)
{
	Vec3 result1(1.0f, 2.f, 3.f);
	result1 *= 2;
	EXPECT_FLOAT_EQ(2.f, result1.x);
	EXPECT_FLOAT_EQ(4.f, result1.y);
	EXPECT_FLOAT_EQ(6.f, result1.z);

	Vec3 result2(1.0f, 2.f, 3.f);
	result2 *= (-3);
	EXPECT_FLOAT_EQ(-3.f, result2.x);
	EXPECT_FLOAT_EQ(-6.f, result2.y);
	EXPECT_FLOAT_EQ(-9.f, result2.z);
}
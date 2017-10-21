#include <gtest/gtest.h>

#include <Math/Vec2.h>

using math::Vec2;

TEST(Vec2, Contructor)
{
	Vec2 defaultConstructor;
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.x);
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.y);

	Vec2 first(1.f, 2.f);
	EXPECT_FLOAT_EQ(1.0f, first.x);
	EXPECT_FLOAT_EQ(2.0f, first.y);

	Vec2 second(-0.1f, -2.f);
	EXPECT_FLOAT_EQ(-0.1f, second.x);
	EXPECT_FLOAT_EQ(-2.0f, second.y);
}

TEST(Vec2, VectorAddition)
{
	Vec2 first(1.f, 2.f);
	Vec2 second(3.f, 4.f);
	Vec2 result = first + second;
	EXPECT_FLOAT_EQ(4.f, result.x);
	EXPECT_FLOAT_EQ(6.f, result.y);

	Vec2 third(-1.f, 2.f);
	Vec2 fourth(3.f, -4.f);
	Vec2 result2 = third + fourth;
	EXPECT_FLOAT_EQ(2.f, result2.x);
	EXPECT_FLOAT_EQ(-2.f, result2.y);
}

TEST(Vec2, VectorAdditionAssignment)
{
	Vec2 result(1.f, 2.f);
	Vec2 first(3.f, 4.f);
	result += first;
	EXPECT_FLOAT_EQ(4.f, result.x);
	EXPECT_FLOAT_EQ(6.f, result.y);

	Vec2 result2(-1.f, 2.f);
	Vec2 second(3.f, -4.f);
	result2 += second;
	EXPECT_FLOAT_EQ(2.f, result2.x);
	EXPECT_FLOAT_EQ(-2.f, result2.y);
}

TEST(Vec2, ScalarMultiplication)
{
	Vec2 first(2.f, 3.f);
	Vec2 result1 = 2 * first;
	EXPECT_FLOAT_EQ(4.f, result1.x);
	EXPECT_FLOAT_EQ(6.f, result1.y);

	Vec2 result2 = first * (-3);
	EXPECT_FLOAT_EQ(-6.f, result2.x);
	EXPECT_FLOAT_EQ(-9.f, result2.y);
}
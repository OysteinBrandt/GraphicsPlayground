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
	Vec3 vec(1.0f, 2.f, 3.f);
	Vec3 result1 = 2 * vec;
	EXPECT_FLOAT_EQ(2.f, result1.x);
	EXPECT_FLOAT_EQ(4.f, result1.y);
	EXPECT_FLOAT_EQ(6.f, result1.z);

	Vec3 result2 = vec * (-3);
	EXPECT_FLOAT_EQ(-3.f, result2.x);
	EXPECT_FLOAT_EQ(-6.f, result2.y);
	EXPECT_FLOAT_EQ(-9.f, result2.z);
}

TEST(Vec3, ScalarDivision)
{
	Vec3 vec(1.0f, 2.f, 3.f);
	Vec3 result1 = 2 / vec;
	EXPECT_FLOAT_EQ(2.f, result1.x);
	EXPECT_FLOAT_EQ(1.f, result1.y);
	EXPECT_FLOAT_EQ(2.f/3.f, result1.z);

	Vec3 result2 = vec / (-3);
	EXPECT_FLOAT_EQ(-(1.f/3.f), result2.x);
	EXPECT_FLOAT_EQ(-(2.f/3.f), result2.y);
	EXPECT_FLOAT_EQ(-1.f, result2.z);
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

TEST(Vec3, Perpendicularity)
{
	Vec3 vec(4, 2);
	Vec3 perpCW = vec.perpCW();
	Vec3 perpCCW = vec.perpCCW();

	EXPECT_FLOAT_EQ(perpCW.x, 2);
	EXPECT_FLOAT_EQ(perpCW.y, -4);
	EXPECT_FLOAT_EQ(perpCCW.x, -2);
	EXPECT_FLOAT_EQ(perpCCW.y, 4);
}

TEST(Vec3, DotProduct)
{
	Vec3 first(1, 2, 3);
	Vec3 second(4, 5, 6);
	float result = first.dot(second);
	EXPECT_FLOAT_EQ(result, 32);

	float result2 = first.dot( Vec3{ 1, -2, -2 } );
	EXPECT_FLOAT_EQ(result2, -9);
}

TEST(Vec3, Length)
{
	auto length = Vec3{ 1, 3, 2 }.length();
	EXPECT_FLOAT_EQ(length, 3.7416573f);

	length = Vec3{ 3, 4, 0 }.length();
	EXPECT_FLOAT_EQ(length, 5);

	length = Vec3{ 3, 0, 0 }.length();
	EXPECT_FLOAT_EQ(length, 3);

	length = Vec3{ 0, 3.145f, 0 }.length();
	EXPECT_FLOAT_EQ(length, 3.145f);

	Vec3 vec{ 0, 0, 2 };
	length = vec.length();
	EXPECT_FLOAT_EQ(length, 2);
}

TEST(Vec3, LengthSquared)
{
	auto lengthSquared = Vec3{ 3, 4, 5 }.lengthSquared();
	EXPECT_FLOAT_EQ(lengthSquared, 50.f);

	Vec3 vec{ 0, -6, 0 };
	EXPECT_FLOAT_EQ(vec.lengthSquared(), 36.0f);
}

TEST(Vec3, Normalization)
{
	auto result = Vec3{ 5, 0, 0 }.normalized();
	EXPECT_FLOAT_EQ(result.length(), 1);
	EXPECT_FLOAT_EQ(result.x, 1);
	EXPECT_FLOAT_EQ(result.y, 0);
	EXPECT_FLOAT_EQ(result.z, 0);

	result = Vec3{ 0, 3, 0 }.normalized();
	EXPECT_FLOAT_EQ(result.length(), 1);
	EXPECT_FLOAT_EQ(result.x, 0);
	EXPECT_FLOAT_EQ(result.y, 1);
	EXPECT_FLOAT_EQ(result.z, 0);

	result = Vec3{ 0, 0, 10 }.normalized();
	EXPECT_FLOAT_EQ(result.length(), 1);
	EXPECT_FLOAT_EQ(result.x, 0);
	EXPECT_FLOAT_EQ(result.y, 0);
	EXPECT_FLOAT_EQ(result.z, 1);

	Vec3 vec{ 0, 0, 0 };
	ASSERT_DEATH(vec.normalized(), "Assertion failed.*");

	result = Vec3{ 1, 2, 3 }.normalized();
	EXPECT_FLOAT_EQ(result.length(), 1);
	EXPECT_FLOAT_EQ(result.x, 0.26726124191242438468455348087975f);
	EXPECT_FLOAT_EQ(result.y, 0.53452248382484876936910696175951f);
	EXPECT_FLOAT_EQ(result.z, 0.80178372573727315405366044263926f);

	result = Vec3{ -3.14f, 2.0f, -7.5f }.normalized();
	EXPECT_FLOAT_EQ(result.length(), 1);
	EXPECT_FLOAT_EQ(result.x, -0.37500832021380991639813072355782f);
	EXPECT_FLOAT_EQ(result.y, 0.23885880268395536076314058825339f);
	EXPECT_FLOAT_EQ(result.z, -0.89572051006483260286177720595021f);

}
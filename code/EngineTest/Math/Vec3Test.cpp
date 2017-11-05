#include <gtest/gtest.h>

#include <Math/Vec3.h>
#include <Math/Constants.h>

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

	Vec3 a{ 0.5f, sqrtf(3.0f) / 2.f };
	Vec3 b{ sqrtf(3.0f) / 2.f, 0.5f };
	auto dotResult = a.dot(b);
	EXPECT_FLOAT_EQ(dotResult, cos(math::PI / 6.0f));
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

void testProjectionOnto(const Vec3 &source, const Vec3 &target)
{
	auto result = source.projectOnto(target);
	auto targetNormal = target.normalized();
	auto expected = source.dot(targetNormal) * targetNormal;
	EXPECT_FLOAT_EQ(result.x, expected.x);
	EXPECT_FLOAT_EQ(result.y, expected.y);
	EXPECT_FLOAT_EQ(result.z, expected.z);
}

TEST(Vec3, ProjectOnto)
{
	Vec3 source{ 2, 4 };
	Vec3 target{ 1, 0 };
	auto result = source.projectOnto(target);
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
	EXPECT_FLOAT_EQ(result.z, 0.0f);

	std::vector<Vec3> vectors
	{
		Vec3{ 1.0f, 2.0f, 3.0f },
		Vec3{ 4.8f, 9.1f, 5.6f },
		Vec3{ 0.0f, 5.0f, 0.0f, },
		Vec3{ -3.2f, -4.9f, 6.7f, },
		Vec3{ 2.4f, 3.1f, -99.6f, },
	};

	for (size_t i = 0; i < vectors.size() - 1; i++)
	{
		testProjectionOnto(vectors[i], vectors[i + 1]);
		testProjectionOnto(vectors[i + 1], vectors[i]);
	}
}

TEST(Vec3, LinearInterpolation)
{
	Vec3 source{ 4.7f, 9.2f, 7.1f };
	Vec3 target{ 7.4f, 2.9f, 1.7f };
	auto diff = target - source;
	float alpha{ 0.0f };
	while (alpha <= 1.0f)
	{
		Vec3 lerpResult1 = lerp(alpha, source, target);
		Vec3 lerpResult2 = source + alpha * diff;
		EXPECT_FLOAT_EQ(lerpResult1.x, lerpResult2.x);
		EXPECT_FLOAT_EQ(lerpResult1.y, lerpResult2.y);
		EXPECT_FLOAT_EQ(lerpResult1.z, lerpResult2.z);
		alpha += 0.01f;
	}
}

TEST(Vec3, CrossProduct)
{
	const Vec3 xdir{ 1.f, 0.f, 0.f };
	const Vec3 zdir{ 0.f, 0.f, -1.f };
	auto res = math::cross(xdir, zdir);
	EXPECT_FLOAT_EQ(0.f, res.x);
	EXPECT_FLOAT_EQ(1.f, res.y);
	EXPECT_FLOAT_EQ(0.f, res.z);

	res = math::cross(res, xdir);
	EXPECT_FLOAT_EQ(zdir.x, res.x);
	EXPECT_FLOAT_EQ(zdir.y, res.y);
	EXPECT_FLOAT_EQ(zdir.z, res.z);

}
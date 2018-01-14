
#include "Sphere.h"
#include "Engine/Math/Constants.h"
#include "Engine/Assert/AssertException.h"

#include <cmath>

namespace engine::generator
{
	SphereGeometry Sphere::generate(unsigned int widthPrecision, unsigned int heightPrecision)
	{
		ENGINE_ASSERT_EXCEPTION_IF(widthPrecision == 0, "Invalid input, devision by 0");
		ENGINE_ASSERT_EXCEPTION_IF(heightPrecision == 0, "Invalid input, devision by 0");

		SphereGeometry result;
#if 0
		result.vertices.reserve((widthPrecision * heightPrecision) + 2);
		
		const auto &first = result.vertices.emplace_back(0.f, 0.f, m_radius);
		const auto width = widthPrecision + 1;
		for (int i = 1; i < width; ++i)	// Start at 1 and end at end + 1 because we are centering the interval
		{
			// TODO: Optimize calculations
			for (int j = 0; j < heightPrecision; ++j)
			{
				result.vertices.emplace_back(
					m_radius * sinf(math::PI * i / width) * cosf(2 * math::PI * j / heightPrecision),
					m_radius * sinf(math::PI * i / width) * sinf(2 * math::PI * j / heightPrecision),
					m_radius * cosf(math::PI * i / width)
				);
			}
		}
		const auto &last = result.vertices.emplace_back(0.f, 0.f, -m_radius);

		//result.indices.reserve();
		for (const auto& vert : result.vertices)
		{

		}
#else
		unsigned int numVerts = (heightPrecision + 1) * (widthPrecision + 1);
		result.normals.reserve(numVerts);
		result.textureCoords.reserve(numVerts);
		result.vertices.reserve(numVerts);
		result.colors.reserve(numVerts);
		for (int i = 0; i <= widthPrecision; ++i)
		{
			float theta = math::PI * i / widthPrecision;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);

			for (int j = 0; j <= heightPrecision; ++j)
			{
				float phi = 2 * math::PI * j / heightPrecision;
				float sinPhi = sinf(phi);
				float cosPhi = cosf(phi);
				const auto &normal = result.normals.emplace_back(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta);
				result.textureCoords.emplace_back(static_cast<float>(1 - (j / heightPrecision)), static_cast<float>(1 - (i / widthPrecision)));
				result.vertices.emplace_back(m_radius * normal.x, m_radius * normal.y, m_radius * normal.z);
				result.colors.emplace_back(normal.x, normal.y, normal.z);
			}
		}
		ENGINE_ASSERT_EXCEPTION_IF(result.vertices.size() > std::numeric_limits<unsigned short>::max(), "Exceeded max number of supported vertices");

		result.indices.reserve(widthPrecision * heightPrecision * 6);
		for (int i = 0; i < widthPrecision; ++i)
		{
			for (int j = 0; j < heightPrecision; ++j)
			{
				int first = (i * (heightPrecision + 1)) + j;
				int second = first + heightPrecision + 1;

				result.indices.emplace_back(first);
				result.indices.emplace_back(second);
				result.indices.emplace_back(first + 1);

				result.indices.emplace_back(second);
				result.indices.emplace_back(second + 1);
				result.indices.emplace_back(first + 1);
			}
		}

#endif

		return result;
	}
}
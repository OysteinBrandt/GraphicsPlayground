#pragma once

#include <string>
#include <chrono>
#include <array>
#include "DllHelper.h"

namespace debug
{
	class OBR_API Profiler
	{
		static const size_t MAX_FRAME_SAMPLES = 1000;
		static const size_t MAX_PROFILE_CATEGORIES = 20;

		struct ProfileCategory
		{
			std::string name;
			std::array<std::chrono::duration<float>, MAX_FRAME_SAMPLES> samples{ std::chrono::seconds(0) };
		} m_categories[MAX_PROFILE_CATEGORIES];

		std::string m_filePath;
		unsigned int m_frameIndex;
		unsigned int m_categoryIndex;
		unsigned int m_numUsedCategories;

	public:
		// TODO: Consider using params for setting buffer size (eg. frameSampleBufferSize, categoryBufferSize )
		Profiler(const std::string &filePath);
		~Profiler();

		void newFrame();

		void addEntry(const std::string &category, const std::chrono::duration<float> &time);

	private:

		char getDelimiter(unsigned int categoryIndex)
		{
			return ((categoryIndex + 1) < m_numUsedCategories) ? ',' : '\n';
		}
	};
}
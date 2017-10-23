#pragma once

#include <string>
#include <chrono>
#include <array>
#include "DllHelper.h"
#include "DebugTools.h"

namespace debug
{
	class OBR_API Profiler
	{
	public:
		static const int MAX_FRAME_SAMPLES = 1000;

#ifdef PROFILING
	private:
		static const size_t MAX_PROFILE_CATEGORIES = 20;
		struct ProfileCategory
		{
			std::string name;
			std::array<std::chrono::duration<float>, MAX_FRAME_SAMPLES> samples{ std::chrono::seconds(0) };
		} m_categories[MAX_PROFILE_CATEGORIES];

		std::string m_filePath;
		int m_frameIndex;
		unsigned int m_categoryIndex;
		unsigned int m_numUsedCategories;

	public:
		// TODO: Consider using params for setting buffer size (eg. frameSampleBufferSize (MAX_FRAME_SAMPLES), categoryBufferSize (MAX_PROFILE_CATEGORIES) )
		Profiler(const std::string &filePath);
		~Profiler();

		void newFrame();
		void addEntry(const std::string &category, const std::chrono::duration<float> &time);

	private:

		bool currentFrameComplete() const;
		void writeData() const;
		void writeFrame(int frameNumber) const;
		bool wrapped() const;

		char getDelimiter(unsigned int categoryIndex) const
		{
			return ((categoryIndex + 1) < m_numUsedCategories) ? ',' : '\n';
		}

#else
	public:
		Profiler(const std::string &filePath) {}

		void newFrame() {}
		void addEntry(const std::string &category, const std::chrono::duration<float> &time) {}
#endif
	};
}
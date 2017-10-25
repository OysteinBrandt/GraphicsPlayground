#include "Profiler.h"

namespace debug{

	details::Profiler& ProfilerSingleton::instance()
	{
		static details::Profiler inst("profiling_result.csv");
		return inst;
	}

}

#ifdef PROFILING
#include <fstream>
#include <cassert> // TODO: Replace with our own assert

namespace debug::details {

static std::ofstream s_stream;	// Not thread safe

Profiler::Profiler(const std::string &filePath) : m_filePath(filePath), m_frameIndex(-1), m_categoryIndex(0), m_numUsedCategories(0)
{
}

Profiler::~Profiler()
{
	writeData();
}

void Profiler::newFrame()
{
	if (m_frameIndex > 0)
		assert(m_categoryIndex == m_numUsedCategories);	// Make sure we are in sync with categories created in frame 0

	++m_frameIndex;
	m_categoryIndex = 0;
}

void Profiler::addEntry(const std::string &category, const std::chrono::milliseconds &time)
{
	assert(!category.empty());
	assert(m_categoryIndex < MAX_PROFILE_CATEGORIES);		// Exceeded maximum amount of categories we can track
	ProfileCategory &pc = m_categories[m_categoryIndex];
	if (m_frameIndex == 0)
	{
		pc.name = category;
		++m_numUsedCategories;
	}
	else
	{
		assert(category == pc.name);											// Unknown category
		assert(m_categoryIndex < m_numUsedCategories);		// Category was not added at frame index 0
	}
	++m_categoryIndex;
	pc.samples[m_frameIndex % MAX_FRAME_SAMPLES] = time;
}


bool Profiler::currentFrameComplete() const
{
	return m_categoryIndex == m_numUsedCategories;
}

void Profiler::writeData() const
{
	s_stream.open(m_filePath, std::ios::trunc);

	for (int c = 0; c < m_numUsedCategories; ++c)
	{
		s_stream << m_categories[c].name;
		s_stream << getDelimiter(c);
	}

	int endIndex{ 0 };
	int startIndex{ 0 };

	if (wrapped())
	{
		endIndex = m_frameIndex % MAX_FRAME_SAMPLES;
		startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;

		while (startIndex != endIndex)
		{
			writeFrame(startIndex);
			startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
		}
		if (currentFrameComplete())
			writeFrame(startIndex);
	}
	else
	{
		auto actualFrames = m_frameIndex;
		if (currentFrameComplete())
			actualFrames++;

		endIndex = actualFrames;
		while (startIndex < endIndex)
			writeFrame(startIndex++);
	}
	s_stream.close();
}

void Profiler::writeFrame(int frameNumber) const
{
	for (int category = 0; category < m_numUsedCategories; ++category)
	{
		s_stream << m_categories[category].samples[frameNumber].count();
		s_stream << getDelimiter(category);
	}
}

bool Profiler::wrapped() const
{
	return m_frameIndex >= MAX_FRAME_SAMPLES && m_frameIndex != -1;
}

} // namespace

#endif // PROFILING
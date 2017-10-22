#include "Profiler.h"
#include <fstream>
#include <cassert> // TODO: Replace with our own assert

namespace debug {

Profiler::Profiler(const std::string &filePath) : m_filePath(filePath), m_frameIndex(0), m_categoryIndex(0), m_numUsedCategories(0)
{
}

Profiler::~Profiler()
{
	std::ofstream stream(m_filePath, std::ios::trunc);

	for (unsigned int i = 0; i < m_numUsedCategories; ++i)
	{
		stream << m_categories[i].name;
		stream << getDelimiter(i);
	}

	for (unsigned int frame = 0; frame < m_frameIndex; ++frame)
	{
		for (unsigned int category = 0; category < m_numUsedCategories; ++category)
		{
			stream << m_categories[category].samples[frame].count();
			stream << getDelimiter(category);
		}
	}
}

void Profiler::newFrame()
{
	if (m_frameIndex <= 0)
		assert(m_categoryIndex > 0);										// Entries should be added before newFrame is called
	else
		assert(m_categoryIndex == m_numUsedCategories);	// Make sure we are in sync with categories created in frame 0
	++m_frameIndex;
	assert(m_frameIndex < MAX_FRAME_SAMPLES);					// Exceeded maximum amout of frames we can track
	m_categoryIndex = 0;
}

void Profiler::addEntry(const std::string &category, const std::chrono::duration<float> &time)
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
	pc.samples[m_frameIndex] = time;
	++m_categoryIndex;
}

}
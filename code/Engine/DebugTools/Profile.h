#pragma once
#include "DebugTools.h"

#ifdef PROFILING

#include "Profiler.h"
#include <chrono>

namespace debug{

class OBR_API Profile
{
	std::chrono::time_point<std::chrono::steady_clock> m_timer;
	std::string m_category;

public:
	Profile(const std::string &category)
	{
		m_category = category;
		m_timer = std::chrono::high_resolution_clock::now();
	}

	~Profile()
	{
		auto now = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<float> diff = now - m_timer;
		ProfilerSingleton::instance().addEntry(m_category, diff);
	}
};

}	// namespace
#endif // PROFILING

#ifdef PROFILING
	#define PROFILE(category) debug::Profile p(category)
	#define NEW_PROFILING_FRAME() debug::ProfilerSingleton::instance().newFrame()
#else
	#define PROFILE(category)
	#define NEW_PROFILING_FRAME()
#endif // PROFILING
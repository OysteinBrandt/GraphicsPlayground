#pragma once
#include "DebugTools.h"

#ifdef PROFILING

#include "Profiler.h"
#include <chrono>

namespace debug {

  class ENGINE_API Profile
  {
    std::chrono::time_point<std::chrono::steady_clock> m_timer;
    std::string m_category;

  public:
    Profile(const std::string &category)
    {
      m_category = category;
      m_timer = std::chrono::steady_clock::now();
    }

    ~Profile()
    {
      auto now = std::chrono::steady_clock::now();
      const std::chrono::duration<float> diff = now - m_timer;
      ProfilerSingleton::instance().addEntry(m_category, std::chrono::duration_cast<std::chrono::milliseconds>(diff));
    }
  };

}	// namespace
#endif // PROFILING

#ifdef PROFILING
#define NEW_PROFILING_FRAME() debug::ProfilerSingleton::instance().newFrame()
#define PROFILE_NAMED_VAR(category, var) debug::Profile var(category)
#define PROFILE(category) PROFILE_NAMED_VAR(category, p)
#else
#define NEW_PROFILING_FRAME()
#define PROFILE_NAMED_VAR(category, var)
#define PROFILE(category)
#endif // PROFILING
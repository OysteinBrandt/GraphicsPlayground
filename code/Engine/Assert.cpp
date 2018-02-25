#include "Assert.h"

#include "Assert/AssertException.h"

namespace engine
{
  thread_local std::vector<std::function<void(const std::string&, Assert::Level, const std::string&, const std::string&, long int)>> Assert::s_handlers;
  std::vector<std::function<void(const std::string&, Assert::Level, const std::string&, const std::string&, long int)>> Assert::s_handlersForAllThreads;

  //void Assert::add(std::function<void(assert::HandlerParam)> /*handler*/, bool /*allThreads*/)
  //{
  //}


  template <typename HandlerFunc>
  void Assert::attach(HandlerFunc& func)
  {
  }

  void Assert::attach(std::function<void(const std::string&, Level, const std::string&, const std::string&, long int)> handler, bool allThreads)
  {
    if (allThreads)
      s_handlersForAllThreads.push_back(handler);
    else
      s_handlers.push_back(handler);
  }

  void Assert::add(const std::string& what, Level severity, const std::string& function, const std::string& file, long int line)
  {
#if defined ENGINE_DEBUG
    if (s_handlers.empty())
    {
      if (severity == Level::Error)
        throw engine::assert::exception(what, function, file, line);
    }
#endif

    // The registered handler must be able to deal with multithreading
    for (const auto& handler : s_handlersForAllThreads)
      handler(what, severity, function, file, line);

    for (const auto& handler : s_handlers)
      handler(what, severity, function, file, line);
  }
}
#ifndef _ENGINE_ASSERT_H_
#define _ENGINE_ASSERT_H_

#include "DllHelper.h"

#include <string>
#include <vector>
#include <functional>

namespace engine
{
  //namespace assert
  //{
  //  struct HandlerParam
  //  {
  //    std::string what;
  //    Assert::Level severity;
  //    std::string functionName;
  //    std::string fileName;
  //    long int line;
  //  };
  //}

  class Assert
  {
  public:
    enum class Level
    {
      Error,
      Warning,
      Info
    };

  private:

    static thread_local std::vector<std::function<void(const std::string&, Level, const std::string&, const std::string&, long int)>> s_handlers;

    // Handlers for all threads must be able to deal with multithreading
    static std::vector<std::function<void(const std::string&, Level, const std::string&, const std::string&, long int)>> s_handlersForAllThreads;

  public:

    //@param: handleAllThreads [The handler must be able to deal with multithreading]
    //ENGINE_API static void add(std::function<void(assert::HandlerParam)> handler, bool allThreads = false);

    template <typename HandlerFunc>
    ENGINE_API static void attach(HandlerFunc& func);

    //@param: handleAllThreads [The handler must be able to deal with multithreading]
    ENGINE_API static void attach(std::function<void(const std::string&, Level, const std::string&, const std::string&, long int)> handler, bool allThreads = false);

    ENGINE_API static void add(const std::string& what, Level severity, const std::string& function, const std::string& file, long int line);
  };
}

#if defined ENGINE_DEBUG 
#define ENGINE_ASSERT(what, level) engine::Assert::add(what, level, __FUNCTION__, __FILE__, __LINE__)
#else
#define ENGINE_ASSERT(what, level) (void)0
#endif

#define ENGINE_ASSERT_INFO(what)    ENGINE_ASSERT(what, engine::Assert::Level::Info)
#define ENGINE_ASSERT_ERROR(what)   ENGINE_ASSERT(what, engine::Assert::Level::Error)
#define ENGINE_ASSERT_WARNING(what) ENGINE_ASSERT(what, engine::Assert::Level::Warning)

// ASSERT_IF
// ...

#endif // !_ENGINE_ASSERT_H_

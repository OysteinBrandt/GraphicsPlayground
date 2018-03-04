#ifndef _ENGINE_ASSERT_H_
#define _ENGINE_ASSERT_H_

#include "DllHelper.h"

#include <string>
#include <vector>
#include <functional>

namespace engine
{
  struct Assert
  {
    enum class Severity
    {
      Error,
      Warning,
      Info
    };
    
    std::string what;
    Severity severity;
    std::string functionName;
    std::string fileName;
    long int line;
  };

  namespace assert
  {
    class HandlerContainer
    {
    private:

      static thread_local std::vector<std::function<void(Assert)>> s_handlers;

      // Must be able to deal with multithreading
      static std::vector<std::function<void(Assert)>> s_handlersForAllThreads;

    public:

      ENGINE_API static void attach(std::function<void(Assert)> handler, bool allThreads = false);

      ENGINE_API static void handle(const Assert& assert);
    };
  }
}

#if defined ENGINE_DEBUG
#define ENGINE_ASSERT(what, severity) engine::assert::HandlerContainer::handle( engine::Assert{ what, severity, __FUNCTION__, __FILE__, __LINE__ } )
#else
#define ENGINE_ASSERT(what, severity) (void)0
#endif

#define ENGINE_ASSERT_INFO(what)    ENGINE_ASSERT(what, engine::Assert::Severity::Info)
#define ENGINE_ASSERT_ERROR(what)   ENGINE_ASSERT(what, engine::Assert::Severity::Error)
#define ENGINE_ASSERT_WARNING(what) ENGINE_ASSERT(what, engine::Assert::Severity::Warning)

// ASSERT_IF
// ...

#endif // !_ENGINE_ASSERT_H_

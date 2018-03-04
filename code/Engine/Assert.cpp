#include "Assert.h"

#include "Assert/AssertException.h"

namespace engine::assert
{
  thread_local std::vector<std::function<void(Assert)>> HandlerContainer::s_handlers;
  std::vector<std::function<void(Assert)>> HandlerContainer::s_handlersForAllThreads;

  /********************************************************************************************************/

  void HandlerContainer::attach(std::function<void(Assert)> handler, bool allThreads)
  {
    if (allThreads)
      s_handlersForAllThreads.push_back(handler);
    else
      s_handlers.push_back(handler);
  }

  /********************************************************************************************************/

  void HandlerContainer::handle(const Assert& assert)
  {
#if defined ENGINE_DEBUG
    if (s_handlers.empty())
    {
      if (assert.severity == Assert::Severity::Error)
        throw engine::assert::exception(assert.what, assert.functionName, assert.fileName, assert.line);
    }
#endif

    // The registered handler must be able to deal with multithreading
    for (const auto& handler : s_handlersForAllThreads)
      handler(assert);

    for (const auto& handler : s_handlers)
      handler(assert);
  }

  /********************************************************************************************************/
}
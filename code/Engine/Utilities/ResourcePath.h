#pragma once

#include "Engine/DllHelper.h"
#include <filesystem>

namespace engine::bad
{
  // Temporary solution for accessing resources
  class Resource
  {
    public:
      ENGINE_API static Resource& instance() 
      {
        static Resource r;
        return r;
      }

    private:
      Resource() {}
      std::filesystem::path m_path;

    public:
      Resource(Resource const&) = delete;
      void operator=(Resource const&) = delete;

      ENGINE_API void path(const std::filesystem::path& p) { m_path = p; }
      ENGINE_API const std::filesystem::path& path() const { return m_path; }
      ENGINE_API std::filesystem::path path_copy() const { return m_path; }
  };
} // namespace engine
#pragma once

#include "IDebugInformationHandler.hpp"

#include <filesystem>
#include <optional>
#include <vector>

namespace CppCoverage
{
  class IModuleSourceFilenamesCache
  {
  public:
    virtual ~IModuleSourceFilenamesCache() = default;

    virtual std::optional<std::vector<std::wstring>> ReadCachedFileNames(const std::filesystem::path&) = 0;
    virtual void CacheFileNames(const std::filesystem::path&, const std::vector<std::wstring>& fileNames) = 0;
  };
}

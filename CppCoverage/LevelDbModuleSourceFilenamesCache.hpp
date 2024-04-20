#pragma once

#include "IModuleSourceFilenamesCache.hpp"

#include <leveldb/db.h>

#include <memory>

namespace CppCoverage
{
  class LevelDbModuleSourceFilenamesCache : public IModuleSourceFilenamesCache
  {
  public:
    explicit LevelDbModuleSourceFilenamesCache(const std::string&);
    ~LevelDbModuleSourceFilenamesCache() override;

    std::optional<std::vector<std::wstring>> ReadCachedFileNames(const std::filesystem::path&) override;
    void CacheFileNames(const std::filesystem::path&, const std::vector<std::wstring>& fileNames) override;
  private:

    leveldb::DB* db_ = nullptr;
  };
}

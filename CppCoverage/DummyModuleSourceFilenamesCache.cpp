#include "stdafx.h"

#include "DummyModuleSourceFilenamesCache.hpp"

namespace CppCoverage
{
	std::optional<std::vector<std::wstring>> DummyModuleSourceFilenamesCache::ReadCachedFileNames(const std::filesystem::path&)
	{
		return std::nullopt;
	}

	void DummyModuleSourceFilenamesCache::CacheFileNames(const std::filesystem::path&, const std::vector<std::wstring>&)
	{

	}
}

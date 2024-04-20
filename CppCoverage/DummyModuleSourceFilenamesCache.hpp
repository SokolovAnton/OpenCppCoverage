#pragma once

#include "IModuleSourceFilenamesCache.hpp"

namespace CppCoverage
{
	class DummyModuleSourceFilenamesCache : public IModuleSourceFilenamesCache
	{
	public:
		~DummyModuleSourceFilenamesCache() override = default;

		std::optional<std::vector<std::wstring>> ReadCachedFileNames(const std::filesystem::path&) override;
		void CacheFileNames(const std::filesystem::path&, const std::vector<std::wstring>&) override;
	};
}

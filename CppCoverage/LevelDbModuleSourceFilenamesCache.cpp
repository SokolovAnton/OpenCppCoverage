#include "stdafx.h"

#include "LevelDbModuleSourceFilenamesCache.hpp"

#include <nlohmann/json.hpp>

#include <locale>
#include <codecvt>

using namespace nlohmann;

namespace
{
	std::string toUtf8(const std::wstring& wideString)
	{
		static auto converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>{};
		return converter.to_bytes(wideString);
	}

	std::wstring fromUtf8(const std::string& string)
	{
		static auto converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>{};
		return converter.from_bytes(string);
	}

	std::string serializeFileNames(const std::vector<std::wstring>& fileNames)
	{
		auto filenamesArray = json::array();
		for (const auto& filename : fileNames)
			filenamesArray.push_back(toUtf8(filename));
		return filenamesArray.dump();
	}

	std::vector<std::wstring> deserializeFileNames(const std::string& jsonData)
	{
		auto fileNamesArray = json::parse(jsonData);
		auto result = std::vector<std::wstring>{};
		result.reserve(fileNamesArray.size());

		for (auto fileName : fileNamesArray)
			result.push_back(fromUtf8(fileName.template get<std::string>()));

		return result;
	}
}

namespace CppCoverage
{
	LevelDbModuleSourceFilenamesCache::LevelDbModuleSourceFilenamesCache(const std::string& directory)
	{
		auto options = leveldb::Options{};
		options.create_if_missing = true;
		auto status = leveldb::DB::Open(options, directory, &db_);

		assert(status.ok());
	}

	LevelDbModuleSourceFilenamesCache::~LevelDbModuleSourceFilenamesCache()
	{
		delete db_;
	}

	std::optional<std::vector<std::wstring>> LevelDbModuleSourceFilenamesCache::ReadCachedFileNames(const std::filesystem::path& path)
	{
		auto readOptions = leveldb::ReadOptions{};
		auto result = std::string{};
		auto status = db_->Get(readOptions, path.string(), &result);
		if (status.IsNotFound())
			return std::nullopt;

		return deserializeFileNames(result);
	}

	void LevelDbModuleSourceFilenamesCache::CacheFileNames(const std::filesystem::path& path, const std::vector<std::wstring>& fileNames)
	{
		auto writeOptions = leveldb::WriteOptions{};
		writeOptions.sync = true;
		db_->Put(writeOptions, path.string(), serializeFileNames(fileNames));
	}
}
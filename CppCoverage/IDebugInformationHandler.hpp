#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace CppCoverage
{
  //-------------------------------------------------------------------------
  class IDebugInformationHandler
  {
  public:
	struct Line
	{
	  Line(unsigned long lineNumber,
		int64_t virtualAddress,
		unsigned long symbolIndex)
		: lineNumber_{ lineNumber },
		virtualAddress_{ virtualAddress },
		symbolIndex_{ symbolIndex }
	  {
	  }
	  Line(const Line&) = default;

	  Line& operator=(const Line&) = default;

	  unsigned long lineNumber_;
	  unsigned long symbolIndex_;
	  int64_t virtualAddress_;
	};

	virtual ~IDebugInformationHandler() = default;
	virtual bool IsSourceFileSelected(const std::filesystem::path&) = 0;
	virtual void OnSourceFile(const std::filesystem::path&,
	  const std::vector<Line>&) = 0;
  };
}

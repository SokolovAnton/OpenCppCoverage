// OpenCppCoverage is an open source code coverage for C++.
// Copyright (C) 2017 OpenCppCoverage
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <filesystem>

#include "CppCoverageExport.hpp"
#include "IModuleSourceFilenamesCache.hpp"
#include "IDebugInformationHandler.hpp"
#include "SubstitutePdbSourcePath.hpp"

struct IDiaSession;
struct IDiaLineNumber;
struct IDiaSourceFile;

namespace CppCoverage
{
	//-------------------------------------------------------------------------
	class CPPCOVERAGE_DLL DebugInformationEnumerator
	{
	  public:
		DebugInformationEnumerator(const std::vector<SubstitutePdbSourcePath>&, IModuleSourceFilenamesCache&);
		bool Enumerate(const std::filesystem::path&,
		               IDebugInformationHandler&);

	  private:
		void
		EnumLines(IDiaSession&, IDiaSourceFile&, IDebugInformationHandler&);
		void
		OnNewLine(IDiaSession&, IDiaLineNumber&, IDebugInformationHandler&);

		std::filesystem::path
		GetSourceFileName(IDiaSourceFile&) const;

		std::vector<IDebugInformationHandler::Line> lines_;
		const std::vector<SubstitutePdbSourcePath> substitutePdbSourcePaths_;

		IModuleSourceFilenamesCache& linesCache_;
	};
}

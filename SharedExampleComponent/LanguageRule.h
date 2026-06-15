#pragma once
#include "Scope.h"
#include <string_view>

namespace ColorCode
{
	struct LanguageRule
	{
		std::wstring_view rawText;
		Scope scope;
	};
}
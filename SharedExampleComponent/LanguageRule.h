#pragma once
#include "Scope.h"

namespace ColorCode
{
	struct LanguageRule
	{
		std::wstring_view rawText;
		Scope scope;
	};
}
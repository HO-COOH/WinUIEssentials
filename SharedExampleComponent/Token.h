#pragma once
#include "Scope.h"

namespace ColorCode
{
	struct Token
	{
		Scope scope;
		size_t start;
		size_t length;
	};
}
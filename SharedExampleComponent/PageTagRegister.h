#pragma once
#include <winrt/base.h>
#include <array>
#include "PageTag.h"

template<typename PageImplType>
struct PageTagRegister
{
	PageTagRegister(auto&&... tags)
	{
		static std::array<std::wstring_view, sizeof...(tags)> storage{tags...};
		PageTag::Registry().push_back(PageTag{ winrt::name_of<typename PageImplType::class_type>(), storage });
	}
};
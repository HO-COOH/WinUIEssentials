#pragma once
#include <span>
#include <string_view>
#include <vector>

struct PageTag
{
	std::wstring_view TypeName;
	std::span<std::wstring_view const> Tags;

	static std::vector<PageTag>& Registry();
};
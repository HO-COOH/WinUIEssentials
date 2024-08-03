#pragma once
#include <string_view>
namespace Utils
{
	HICON GetHIcon(std::wstring_view path);

	HICON GetHIcon(winrt::Windows::Foundation::Uri uri);
}

#include "pch.h"
#include "User32String.h"

winrt::hstring User32String::loadString(UINT id, wchar_t const* fallback) const
{
    wchar_t const* text{};
    auto const length = LoadStringW(m_user32Module, id, reinterpret_cast<LPWSTR>(&text), 0);
    if (length <= 0 || !text)
        return winrt::hstring{ fallback };
    return winrt::hstring{ text, static_cast<winrt::hstring::size_type>(length) };
}

//String ids used by win32k for its own caption button tooltips
winrt::hstring User32String::Minimize() const
{
	return loadString(900, L"Minimize");
}

winrt::hstring User32String::RestoreDown() const
{
	return loadString(903, L"Restore Down");
}

winrt::hstring User32String::Maximize() const
{
	return loadString(901, L"Maximize");
}

winrt::hstring User32String::Close() const
{
	return loadString(905, L"Close");
}

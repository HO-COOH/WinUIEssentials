#pragma once
#include <Windows.h>
#include <winrt/base.h>

class User32String
{
	HMODULE m_user32Module{GetModuleHandleW(L"User32.dll")};
	winrt::hstring loadString(UINT id, wchar_t const* fallback) const;
public:
	winrt::hstring Minimize() const;
	winrt::hstring RestoreDown() const;
	winrt::hstring Maximize() const;
	winrt::hstring Close() const;
};
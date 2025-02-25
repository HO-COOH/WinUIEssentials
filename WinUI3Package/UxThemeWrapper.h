#pragma once
#include "PreferredAppMode.h"
#include <wil/resource.h>

/**
 * This class wraps up a call to `SetPreferredAppMode` defined in `uxtheme.dll`
 */
class UxTheme
{
	using FnSetPreferredAppMode = PreferredAppMode(WINAPI*)(PreferredAppMode);
	using FnFlushMenuThemes = void(WINAPI*)();
	wil::unique_hmodule hUxTheme{ LoadLibraryEx(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32) };
public:
	void SetPreferredAppMode(PreferredAppMode value);
};

#include "pch.h"
#include "UxThemeWrapper.h"

void UxTheme::SetPreferredAppMode(PreferredAppMode value)
{
	auto fnSetPreferredAppMode = reinterpret_cast<FnSetPreferredAppMode>(GetProcAddress(hUxTheme.get(), MAKEINTRESOURCEA(135)));
	if (fnSetPreferredAppMode)
		fnSetPreferredAppMode(value);
}

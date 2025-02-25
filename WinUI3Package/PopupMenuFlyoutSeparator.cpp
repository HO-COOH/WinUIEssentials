#include "pch.h"
#include "PopupMenuFlyoutSeparator.h"
#if __has_include("PopupMenuFlyoutSeparator.g.cpp")
#include "PopupMenuFlyoutSeparator.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::WinUI3Package::PopupMenuFlyoutItemType PopupMenuFlyoutSeparator::Type()
	{
		return winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutSeparator;
	}
}

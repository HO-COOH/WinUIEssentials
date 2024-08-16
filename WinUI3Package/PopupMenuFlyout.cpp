#include "pch.h"
#include "PopupMenuFlyout.h"
#if __has_include("PopupMenuFlyout.g.cpp")
#include "PopupMenuFlyout.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> PopupMenuFlyout::Items()
	{
		return nullptr;
	}
	void PopupMenuFlyout::Items(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> value)
	{
	}
}

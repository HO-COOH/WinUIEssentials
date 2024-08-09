#pragma once
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Foundation.Collections.h>

void ForEachMenuItem(
	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> const& items,
	auto&& fMenuFlyoutItem,
	auto&& fMenuFlyoutSeparator,
	auto&& fMenuFlyoutSubItem,
	auto&& fToggleMenuFlyoutItem)
{
	for (auto const& item : items)
	{
		if (auto menuFlyoutItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>())
		{
			if (auto toggleMenuFlyoutItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::ToggleMenuFlyoutItem>())
				fToggleMenuFlyoutItem(toggleMenuFlyoutItem);
			else
				fMenuFlyoutItem(menuFlyoutItem);
		}
		else if (auto separator = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSeparator>())
		{
			fMenuFlyoutSeparator(separator);
		}
		else if (auto subItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSubItem>())
		{
			fMenuFlyoutSubItem(subItem);
		}
		else
			assert(false);
	}
}

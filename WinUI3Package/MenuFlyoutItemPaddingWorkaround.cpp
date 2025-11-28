#include "pch.h"
#include "MenuFlyoutItemPaddingWorkaround.h"

MenuFlyoutItemPaddingWorkaround::ItemKindCount MenuFlyoutItemPaddingWorkaround::applyImpl(
	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> const& items)
{
	ItemKindCount count{};
	for (auto item : items)
	{
		if (item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSeparator>())
		{
			++count.numSeparators;
			continue;
		}
	
		++count.numNormalItems;
		item.Height(ForceHeight);
		item.Padding(ForcePadding);

		if (auto subItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSubItem>())
			applyImpl(subItem.Items());
	}
	return count;
}

void MenuFlyoutItemPaddingWorkaround::Apply(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu)
{
	auto [numNormalItems, numSeparators] = applyImpl(menu.Items());
	winrt::Microsoft::UI::Xaml::Setter setter
	{
		winrt::Microsoft::UI::Xaml::FrameworkElement::MaxHeightProperty(),
		winrt::box_value(numNormalItems * (ForceHeight + ForcePadding.Top + ForcePadding.Bottom))
	};
	if (auto style = menu.MenuFlyoutPresenterStyle())
		style.Setters().Append(setter);
	else
	{
		winrt::Microsoft::UI::Xaml::Style newStyle{ winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutPresenter>() };
		newStyle.Setters().Append(setter);
		menu.MenuFlyoutPresenterStyle(newStyle);
	}
}

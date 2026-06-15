#include "pch.h"
#include "MenuFlyoutItemPaddingWorkaround.h"

static bool hasTemplateSetter(winrt::Microsoft::UI::Xaml::Style style)
{
	while (style)
	{
		for (auto setterBase : style.Setters())
		{
			if (auto setter = setterBase.try_as<winrt::Microsoft::UI::Xaml::Setter>())
			{
				if (setter.Property() == winrt::Microsoft::UI::Xaml::Controls::Control::TemplateProperty())
					return true;
			}
		}
		style = style.BasedOn();
	}
	return false;
}

static bool hasCustomTemplate(winrt::Microsoft::UI::Xaml::Controls::Control const& control)
{
	if (control.ReadLocalValue(winrt::Microsoft::UI::Xaml::Controls::Control::TemplateProperty()) != winrt::Microsoft::UI::Xaml::DependencyProperty::UnsetValue())
		return true;
	return hasTemplateSetter(control.Style());
}

void MenuFlyoutItemPaddingWorkaround::applyImpl(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> const& items)
{
	for (auto item : items)
	{
		if (item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSeparator>())
			continue;

		auto subItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSubItem>();

		if (!hasCustomTemplate(item))
		{
			item.Height(ForceHeight);
			item.Padding(ForcePadding);
		}

		if (subItem)
			applyImpl(subItem.Items());
	}
}

void MenuFlyoutItemPaddingWorkaround::Apply(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu)
{
	applyImpl(menu.Items());
}

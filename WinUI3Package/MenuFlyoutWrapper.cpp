#include "pch.h"
#include "MenuFlyoutWrapper.h"
#include <winrt/Microsoft.UI.Xaml.h>
#include "MenuFlyoutItemPaddingWorkaround.h"


MenuFlyoutWrapper::MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& flyout) : m_menu{flyout}
{
	m_menu.ShouldConstrainToRootBounds(false);

	//TODO: Fix theme
	
	//winrt::Microsoft::UI::Xaml::Style style{ winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutPresenter>() };
	//winrt::Microsoft::UI::Xaml::Setter setter{ winrt::Microsoft::UI::Xaml::FrameworkElement::RequestedThemeProperty(), winrt::box_value(winrt::Microsoft::UI::Xaml::ElementTheme::Light) };
	//style.Setters().Append(setter);
	//m_menu.as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>().MenuFlyoutPresenterStyle(style);
}

void MenuFlyoutWrapper::Show(POINT p)
{
	m_menuHost.Move(p);
	ShowAt(m_menu.as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>(), m_menuHost);
}

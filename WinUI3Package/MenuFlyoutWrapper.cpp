#include "pch.h"
#include "MenuFlyoutWrapper.h"
#include <winrt/Microsoft.UI.Xaml.h>
#include "MenuFlyoutItemPaddingWorkaround.h"
#include <shellscalingapi.h>
#include <IconUtils.h>

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
	auto const monitor = MonitorFromPoint(p, MONITOR_DEFAULTTONEAREST);
	UINT dpiX, dpiY{};
	GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
	auto offset = Utils::ScaleForDpi(24, dpiX);
	p.x = max(0, p.x - offset);
	m_menuHost.Move(p);
	ShowAtImpl(m_menu.as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>(), m_menuHost);
}

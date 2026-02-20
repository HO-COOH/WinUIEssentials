#include "pch.h"
#include "MenuFlyoutWrapper.h"
#include <winrt/Microsoft.UI.Xaml.h>
#include "MenuFlyoutItemPaddingWorkaround.h"
#include <shellscalingapi.h>
#include <IconUtils.h>
#include "ThemeSettingsImpl.hpp"

MenuFlyoutWrapper::MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& flyout) : m_menu{flyout}
{
	m_menu.ShouldConstrainToRootBounds(false);
}

void MenuFlyoutWrapper::applySystemTheme()
{
	m_menuHost.RequestedTheme(
		ThemeSettingsImpl::SystemUsesLightTheme()
			? winrt::Microsoft::UI::Xaml::ElementTheme::Light
			: winrt::Microsoft::UI::Xaml::ElementTheme::Dark
	);
}

void MenuFlyoutWrapper::Theme(winrt::Microsoft::UI::Xaml::ElementTheme value)
{
	MenuBase::Theme(value);
	if (value == winrt::Microsoft::UI::Xaml::ElementTheme::Default)
	{
		applySystemTheme();
		m_themeListenerToken = ThemeListener::Add([this]() {
			applySystemTheme();
		});
	}
	else
	{
		m_menuHost.RequestedTheme(value);
		m_themeListenerToken.reset();
	}
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

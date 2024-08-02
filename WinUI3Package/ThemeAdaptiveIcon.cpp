#include "pch.h"
#include "ThemeAdaptiveIcon.h"
#include "GuidWrapper.h"
#include "TaskbarIconMessageWindow.h"
#include "AppsUseLightTheme.h"

void ThemeAdaptiveIcon::onThemeChanged(winrt::Microsoft::UI::Xaml::ApplicationTheme theme)
{
	m_iconData.hIcon(theme == winrt::Microsoft::UI::Xaml::ApplicationTheme::Light ? m_iconLight : m_iconDark);
	m_iconData.Modify();
}

ThemeAdaptiveIcon::ThemeAdaptiveIcon(HICON iconLight, HICON iconDark) :
	m_iconLight{iconLight},
	m_iconDark{iconDark},
	m_themeListenerToken{ThemeListener::Add(std::bind(&ThemeAdaptiveIcon::onThemeChanged, this, std::placeholders::_1))}
{
	m_iconData.guidItem(GuidWrapper{});
	m_iconData.hWnd(TaskbarIconMessageWindow::Get());
	m_iconData.hIcon(AppsUseLightTheme{} == winrt::Microsoft::UI::Xaml::ApplicationTheme::Light ? m_iconLight : m_iconDark);
	m_iconData.Add();
}

ThemeAdaptiveIcon::~ThemeAdaptiveIcon()
{
	m_iconData.Delete();
}

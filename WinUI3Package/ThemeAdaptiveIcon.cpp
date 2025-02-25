#include "pch.h"
#include "ThemeAdaptiveIcon.h"
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
	Show();
}

void ThemeAdaptiveIcon::addOnThemeChangedIfSet()
{
	if (m_iconLight && m_iconDark)
		m_themeListenerToken = ThemeListener::Add(std::bind(&ThemeAdaptiveIcon::onThemeChanged, this, std::placeholders::_1));
}

ThemeAdaptiveIcon& ThemeAdaptiveIcon::IconLight(HICON value)
{
	m_iconLight = value;
	return *this;
}

ThemeAdaptiveIcon& ThemeAdaptiveIcon::IconDark(HICON value)
{
	m_iconDark = value;
	return *this;
}

void ThemeAdaptiveIcon::Show()
{
	m_iconData.hIcon(AppsUseLightTheme{} == winrt::Microsoft::UI::Xaml::ApplicationTheme::Light ? m_iconLight : m_iconDark);
	addOnThemeChangedIfSet();
	TaskbarIconBase::Show();
}

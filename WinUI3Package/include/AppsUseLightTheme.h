#pragma once
#include <wil/registry.h>
#include <optional>
#include <winrt/Microsoft.UI.Xaml.h>

class AppsUseLightTheme
{
	DWORD m_value;
public:
	constexpr AppsUseLightTheme(std::optional<DWORD> value) : m_value{ value.value_or(1) } {}

	AppsUseLightTheme() : AppsUseLightTheme{
		wil::reg::try_get_value_dword(
			HKEY_CURRENT_USER,
			LR"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)",
			L"AppsUseLightTheme"
		)
	}
	{
	}

	constexpr operator winrt::Microsoft::UI::Xaml::ApplicationTheme() const
	{
		return m_value == 1 ? winrt::Microsoft::UI::Xaml::ApplicationTheme::Light :
			winrt::Microsoft::UI::Xaml::ApplicationTheme::Dark;
	}
};
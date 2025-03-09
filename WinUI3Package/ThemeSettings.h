#pragma once

#include "ThemeSettings.g.h"
#include "PropertyChangeHelper.hpp"
#include <winrt/Windows.UI.h>
#include "ThemeListener.h"

namespace winrt::WinUI3Package::implementation
{
	struct ThemeSettings : ThemeSettingsT<ThemeSettings>, MvvmHelper::PropertyChangeHelper<ThemeSettings>
    {
        static winrt::WinUI3Package::ThemeSettings Instance();

        bool AppsUseLightTheme();
        bool ColorPrevalence();
		bool EnableTransparency();
		bool SystemUsesLightTheme();

		winrt::Windows::UI::Color AccentColor();
		winrt::Microsoft::UI::Xaml::Media::SolidColorBrush AccentColorBrush();
		winrt::Windows::UI::Color ColorizationColor();
        winrt::Microsoft::UI::Xaml::Media::SolidColorBrush ColorizationColorBrush();

		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ColorHistory();
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ColorHistoryBrushes();
    private:
        constexpr static winrt::Windows::UI::Color fromDWORD(DWORD value)
        {
            return winrt::Windows::UI::Color
            {
                .A = 0xFF,
                .R = static_cast<uint8_t>((value >> 16) & 0xFF),
                .G = static_cast<uint8_t>((value >> 8) & 0xFF),
                .B = static_cast<uint8_t>(value & 0xFF)
            };
        }

        ThemeListener::Token m_token = ThemeListener::Add([this]() {
			raisePropertyChange(L"AppsUseLightTheme");
			raisePropertyChange(L"ColorPrevalence");
			raisePropertyChange(L"EnableTransparency");
			raisePropertyChange(L"SystemUsesLightTheme");
			raisePropertyChange(L"AccentColor");
			raisePropertyChange(L"AccentColorBrush");
			raisePropertyChange(L"ColorizationColor");
			raisePropertyChange(L"ColorizationColorBrush");
        });
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ThemeSettings : ThemeSettingsT<ThemeSettings, implementation::ThemeSettings>
    {
    };
}

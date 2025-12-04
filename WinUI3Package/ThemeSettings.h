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

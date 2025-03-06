#include "pch.h"
#include "ThemeSettings.h"
#if __has_include("ThemeSettings.g.cpp")
#include "ThemeSettings.g.cpp"
#endif
#include "ThemeSettingsImpl.hpp"


namespace winrt::WinUI3Package::implementation
{
	winrt::WinUI3Package::ThemeSettings ThemeSettings::Instance()
    {
        static auto instance = winrt::make<ThemeSettings>();
        return instance;
    }

	bool ThemeSettings::AppsUseLightTheme()
	{
		return ThemeSettingsImpl::AppsUseLightTheme();
	}

	bool ThemeSettings::ColorPrevalence()
	{
		return ThemeSettingsImpl::ColorPrevalence();
	}

	bool ThemeSettings::EnableTransparency()
	{
		return ThemeSettingsImpl::EnableTransparency();
	}

	bool ThemeSettings::SystemUsesLightTheme()
	{
		return ThemeSettingsImpl::SystemUsesLightTheme();
	}

	winrt::Windows::UI::Color ThemeSettings::AccentColor()
	{
		return fromDWORD(ThemeSettingsImpl::AccentColor());
	}

	winrt::Microsoft::UI::Xaml::Media::SolidColorBrush ThemeSettings::AccentColorBrush()
	{
		return winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ AccentColor() };
	}

	winrt::Windows::UI::Color ThemeSettings::ColorizationColor()
	{
		return fromDWORD(ThemeSettingsImpl::ColorizationColor());
	}

	winrt::Microsoft::UI::Xaml::Media::SolidColorBrush ThemeSettings::ColorizationColorBrush()
	{
		return winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ ColorizationColor() };
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ThemeSettings::ColorHistory()
	{
		std::vector<winrt::Windows::Foundation::IInspectable> colors(ThemeSettingsImpl::ColorHistory().size());
		std::transform(
			colors.begin(),
			colors.end(),
			colors.begin(),
			[i = 0](auto const&)mutable
			{
				return winrt::box_value(fromDWORD(ThemeSettingsImpl::ColorHistory()[i++]));
			}
		);
		return winrt::single_threaded_vector(std::move(colors));
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ThemeSettings::ColorHistoryBrushes()
	{
		std::vector<winrt::Windows::Foundation::IInspectable> colors(ThemeSettingsImpl::ColorHistory().size());
		std::transform(
			colors.begin(),
			colors.end(),
			colors.begin(),
			[i = 0](auto const&)mutable
			{
				return winrt::Microsoft::UI::Xaml::Media::SolidColorBrush
				{ 
					fromDWORD(ThemeSettingsImpl::ColorHistory()[i++]) 
				};
			}
		);
		return winrt::single_threaded_vector(std::move(colors));
	}
}

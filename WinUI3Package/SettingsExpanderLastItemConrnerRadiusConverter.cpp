#include "pch.h"
#include "SettingsExpanderLastItemConrnerRadiusConverter.h"
#if __has_include("SettingsExpanderLastItemConrnerRadiusConverter.g.cpp")
#include "SettingsExpanderLastItemConrnerRadiusConverter.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Windows::Foundation::IInspectable SettingsExpanderLastItemConrnerRadiusConverter::Convert(
		winrt::Windows::Foundation::IInspectable const& value,
		winrt::Windows::UI::Xaml::Interop::TypeName const&,
		winrt::Windows::Foundation::IInspectable const&,
		winrt::hstring const&)
	{
		if (auto cornerRadius = value.try_as<winrt::Microsoft::UI::Xaml::CornerRadius>())
		{
			return winrt::box_value(winrt::Microsoft::UI::Xaml::CornerRadius{
				.TopLeft = 0,
				.TopRight = 0,
				.BottomRight = cornerRadius->BottomRight,
				.BottomLeft = cornerRadius->BottomLeft
			});
		}
		return value;
	}

	winrt::Windows::Foundation::IInspectable SettingsExpanderLastItemConrnerRadiusConverter::ConvertBack(
		winrt::Windows::Foundation::IInspectable const& value,
		winrt::Windows::UI::Xaml::Interop::TypeName const&,
		winrt::Windows::Foundation::IInspectable const&,
		winrt::hstring const&)
	{
		return value;
	}
}

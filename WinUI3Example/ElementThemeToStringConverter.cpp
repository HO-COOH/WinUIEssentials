#include "pch.h"
#include "ElementThemeToStringConverter.h"
#if __has_include("ElementThemeToStringConverter.g.cpp")
#include "ElementThemeToStringConverter.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	winrt::Windows::Foundation::IInspectable ElementThemeToStringConverter::Convert(
		winrt::Windows::Foundation::IInspectable const& value,
		winrt::Windows::UI::Xaml::Interop::TypeName const&,
		winrt::Windows::Foundation::IInspectable const&,
		winrt::hstring const&)
	{
		switch (winrt::unbox_value<winrt::Microsoft::UI::Xaml::ElementTheme>(value))
		{
			case winrt::Microsoft::UI::Xaml::ElementTheme::Default:
				return winrt::box_value(L"Default");
			case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
				return winrt::box_value(L"Light");
			case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
				return winrt::box_value(L"Dark");
		}
	}

	winrt::Windows::Foundation::IInspectable ElementThemeToStringConverter::ConvertBack(
		winrt::Windows::Foundation::IInspectable const& value,
		winrt::Windows::UI::Xaml::Interop::TypeName const&,
		winrt::Windows::Foundation::IInspectable const&,
		winrt::hstring const&)
	{
		throw winrt::hresult_not_implemented{};
	}
}

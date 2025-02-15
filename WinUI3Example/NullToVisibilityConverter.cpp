#include "pch.h"
#include "NullToVisibilityConverter.h"
#if __has_include("NullToVisibilityConverter.g.cpp")
#include "NullToVisibilityConverter.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    winrt::Windows::Foundation::IInspectable NullToVisibilityConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value, 
        winrt::Windows::UI::Xaml::Interop::TypeName const&, 
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::hstring const&)
    {
        return winrt::box_value(value ? winrt::Microsoft::UI::Xaml::Visibility::Visible : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }
    winrt::Windows::Foundation::IInspectable NullToVisibilityConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::Interop::TypeName const&, winrt::Windows::Foundation::IInspectable const&, winrt::hstring const&)
    {
        return winrt::Windows::Foundation::IInspectable();
    }
}

#include "pch.h"
#include "ReferenceToVisibilityConverter.h"
#if __has_include("ReferenceToVisibilityConverter.g.cpp")
#include "ReferenceToVisibilityConverter.g.cpp"
#endif
#include "Convert.h"

namespace winrt::PackageRoot::implementation
{

    winrt::Windows::Foundation::IInspectable ReferenceToVisibilityConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value, 
        winrt::Windows::UI::Xaml::Interop::TypeName const&, 
        winrt::Windows::Foundation::IInspectable const& parameter, 
        winrt::hstring const&)
    {
        auto visibility = Convert::ReferenceToVisibility(value);
        if (Reverse() || (parameter && winrt::unbox_value<winrt::hstring>(parameter) == L"Reverse"))
            visibility = visibility == winrt::WinUINamespace::UI::Xaml::Visibility::Visible ? winrt::WinUINamespace::UI::Xaml::Visibility::Collapsed : winrt::WinUINamespace::UI::Xaml::Visibility::Visible;

        return winrt::box_value(visibility);
    }

    winrt::Windows::Foundation::IInspectable ReferenceToVisibilityConverter::ConvertBack(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Windows::UI::Xaml::Interop::TypeName const&, 
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::hstring const&)
    {
        throw winrt::hresult_not_implemented{};
    }
}

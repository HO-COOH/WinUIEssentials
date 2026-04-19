#include "pch.h"
#include "Convert.h"
#if __has_include("Convert.g.cpp")
#include "Convert.g.cpp"
#endif
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace winrt::PackageRoot::implementation
{
    winrt::hstring Convert::DoubleToString(double value)
    {
        return winrt::to_hstring(value);
    }

    winrt::hstring Convert::DoubleToString(double value, int32_t precision)
    {
        std::wostringstream stream;
        stream << std::fixed << std::setprecision((std::max)(0, precision)) << value;
        return winrt::hstring{ stream.str() };
    }

    bool Convert::ContainerToBool(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container)
    {
        return container && container.Size() > 0;
    }
    bool Convert::ReferenceToBool(Windows::Foundation::IInspectable const& value)
    {
        return value != nullptr;
    }
    bool Convert::StringToBool(hstring const& value)
    {
        return !value.empty();
    }

    bool Convert::ContainerToBoolReverse(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container)
    {
        return !ContainerToBool(container);
    }
    bool Convert::ReferenceToBoolReverse(Windows::Foundation::IInspectable const& value)
    {
        return !ReferenceToBool(value);
    }
    bool Convert::StringToBoolReverse(hstring const& value)
    {
        return !StringToBool(value);
    }

    winrt::WindowsNamespace::UI::Xaml::Visibility Convert::ContainerToVisibility(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& container)
    {
        return ContainerToBool(container) ? winrt::WindowsNamespace::UI::Xaml::Visibility::Visible : winrt::WindowsNamespace::UI::Xaml::Visibility::Collapsed;
    }

    winrt::WindowsNamespace::UI::Xaml::Visibility Convert::ReferenceToVisibility(winrt::Windows::Foundation::IInspectable const& value)
    {
        return ReferenceToBool(value) ? winrt::WindowsNamespace::UI::Xaml::Visibility::Visible : winrt::WindowsNamespace::UI::Xaml::Visibility::Collapsed;
    }

    winrt::WindowsNamespace::UI::Xaml::Visibility Convert::StringToVisibility(winrt::hstring const& value)
    {
        return StringToBool(value) ? winrt::WindowsNamespace::UI::Xaml::Visibility::Visible : winrt::WindowsNamespace::UI::Xaml::Visibility::Collapsed;
    }

    winrt::WindowsNamespace::UI::Xaml::Visibility Convert::ContainerToVisibilityReverse(winrt::Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container)
    {
        return ContainerToBool(container) ? winrt::WindowsNamespace::UI::Xaml::Visibility::Collapsed : winrt::WindowsNamespace::UI::Xaml::Visibility::Visible;
    }

    winrt::WindowsNamespace::UI::Xaml::Visibility Convert::ReferenceToVisibilityReverse(winrt::Windows::Foundation::IInspectable const& value)
    {
        return ReferenceToBool(value) ? winrt::WindowsNamespace::UI::Xaml::Visibility::Collapsed : winrt::WindowsNamespace::UI::Xaml::Visibility::Visible;
    }

    winrt::WindowsNamespace::UI::Xaml::Visibility Convert::StringToVisibilityReverse(winrt::hstring const& value)
    {
        return StringToBool(value) ? winrt::WindowsNamespace::UI::Xaml::Visibility::Collapsed : winrt::WindowsNamespace::UI::Xaml::Visibility::Visible;
    }
}

#include "pch.h"
#include "Convert.h"
#if __has_include("Convert.g.cpp")
#include "Convert.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
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

    Microsoft::UI::Xaml::Visibility Convert::ContainerToVisibility(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container)
    {
        return ContainerToBool(container) ? Microsoft::UI::Xaml::Visibility::Visible : Microsoft::UI::Xaml::Visibility::Collapsed;
    }
    Microsoft::UI::Xaml::Visibility Convert::ReferenceToVisibility(Windows::Foundation::IInspectable const& value)
    {
        return ReferenceToBool(value) ? Microsoft::UI::Xaml::Visibility::Visible : Microsoft::UI::Xaml::Visibility::Collapsed;
    }
    Microsoft::UI::Xaml::Visibility Convert::StringToVisibility(hstring const& value)
    {
        return StringToBool(value) ? Microsoft::UI::Xaml::Visibility::Visible : Microsoft::UI::Xaml::Visibility::Collapsed;
    }

    Microsoft::UI::Xaml::Visibility Convert::ContainerToVisibilityReverse(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container)
    {
        return ContainerToBool(container) ? Microsoft::UI::Xaml::Visibility::Collapsed : Microsoft::UI::Xaml::Visibility::Visible;
    }
    Microsoft::UI::Xaml::Visibility Convert::ReferenceToVisibilityReverse(Windows::Foundation::IInspectable const& value)
    {
        return ReferenceToBool(value) ? Microsoft::UI::Xaml::Visibility::Collapsed : Microsoft::UI::Xaml::Visibility::Visible;
    }
    Microsoft::UI::Xaml::Visibility Convert::StringToVisibilityReverse(hstring const& value)
    {
        return StringToBool(value) ? Microsoft::UI::Xaml::Visibility::Collapsed : Microsoft::UI::Xaml::Visibility::Visible;
    }
}

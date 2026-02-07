#include "pch.h"
#include "CustomBackdropBase.h"
#if __has_include("CustomBackdropBase.g.cpp")
#include "CustomBackdropBase.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::s_enableWhenInactiveProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"EnableWhenInactive",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
        );

    bool CustomBackdropBase::EnableWhenInactive()
    {
        return winrt::unbox_value<bool>(GetValue(EnableWhenInactiveProperty()));
    }

    void CustomBackdropBase::EnableWhenInactive(bool value)
    {
        SetValue(EnableWhenInactiveProperty(), winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::EnableWhenInactiveProperty()
    {
        return s_enableWhenInactiveProperty;
    }

    void CustomBackdropBase::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
    }

    void CustomBackdropBase::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
    {
    }

    void CustomBackdropBase::OnDefaultSystemBackdropConfigurationChanged(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
    }

}

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

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::s_fallbackColorProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"FallbackColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Windows::UI::Color{}), &CustomBackdropBase::onFallbackColorChanged}
        );


    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::s_luminosityOpacityProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"LuminosityOpacity",
            winrt::xaml_typename<float>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{winrt::box_value(0.f), &CustomBackdropBase::onLuminosityOpacityChanged}
        );

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::s_tintColorProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"TintColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Windows::UI::Color{}), &CustomBackdropBase::onTintColorChanged }
        );

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::s_tintOpacityProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"TintOpacity",
            winrt::xaml_typename<float>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{winrt::box_value(0.f), &CustomBackdropBase::onTintOpacityChanged}
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

    winrt::Windows::UI::Color CustomBackdropBase::FallbackColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(FallbackColorProperty()));
    }

    void CustomBackdropBase::FallbackColor(winrt::Windows::UI::Color value)
    {
        SetValue(FallbackColorProperty(), winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::FallbackColorProperty()
    {
        return s_fallbackColorProperty;
    }

    float CustomBackdropBase::LuminosityOpacity()
    {
        return winrt::unbox_value<float>(GetValue(LuminosityOpacityProperty()));
    }

    void CustomBackdropBase::LuminosityOpacity(float value)
    {
        SetValue(LuminosityOpacityProperty(), winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::LuminosityOpacityProperty()
    {
        return s_luminosityOpacityProperty;
    }

    winrt::Windows::UI::Color CustomBackdropBase::TintColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(TintColorProperty()));
    }

    void CustomBackdropBase::TintColor(winrt::Windows::UI::Color value)
    {
        SetValue(TintColorProperty(), winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::TintColorProperty()
    {
        return s_tintColorProperty;
    }

    float CustomBackdropBase::TintOpacity()
    {
        return winrt::unbox_value<float>(GetValue(TintOpacityProperty()));
    }
    void CustomBackdropBase::TintOpacity(float value)
    {
        SetValue(TintOpacityProperty(), winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty CustomBackdropBase::TintOpacityProperty()
    {
        return s_tintOpacityProperty;
    }

    void CustomBackdropBase::onFallbackColorChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
        winrt::get_self<CustomBackdropBase>(d.as<class_type>())->OnFallbackColorChanged(args);
    }

    void CustomBackdropBase::onLuminosityOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
        winrt::get_self<CustomBackdropBase>(d.as<class_type>())->OnLuminosityOpacityChanged(args);
    }

    void CustomBackdropBase::onTintColorChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
        winrt::get_self<CustomBackdropBase>(d.as<class_type>())->OnTintColorChanged(args);
    }

    void CustomBackdropBase::onTintOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
        winrt::get_self<CustomBackdropBase>(d.as<class_type>())->OnTintOpacityChanged(args);
    }

    #pragma region VirtualFunctions
    void CustomBackdropBase::OnFallbackColorChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
    }

    void CustomBackdropBase::OnLuminosityOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
    }

    void CustomBackdropBase::OnTintColorChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
    }

    void CustomBackdropBase::OnTintOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
    {
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
    #pragma endregion 
}

#include "pch.h"
#include "UIElementExtension.h"
#if __has_include("UIElementExtension.g.cpp")
#include "UIElementExtension.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty UIElementExtension::s_clipToBoundsProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ClipToBounds",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &UIElementExtension::onClipToBoundsPropertyChanged }
    );
    winrt::Microsoft::UI::Xaml::DependencyProperty UIElementExtension::ClipToBoundsProperty()
    {
        return s_clipToBoundsProperty;
    }
    bool UIElementExtension::GetClipToBounds(winrt::Microsoft::UI::Xaml::UIElement element)
    {
        return winrt::unbox_value<bool>(element.GetValue(s_clipToBoundsProperty));
    }
    void UIElementExtension::SetClipToBounds(winrt::Microsoft::UI::Xaml::UIElement element, bool value)
    {
        element.SetValue(s_clipToBoundsProperty, winrt::box_value(value));
    }

    void UIElementExtension::onClipToBoundsPropertyChanged(
        winrt::Microsoft::UI::Xaml::DependencyObject d, 
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto element = d.try_as<winrt::Microsoft::UI::Xaml::UIElement>())
        {
            auto const value = winrt::unbox_value<bool>(e.NewValue());
            auto visual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(element);
            visual.Clip(value ? visual.Compositor().CreateInsetClip() : nullptr);
        }
    }
}

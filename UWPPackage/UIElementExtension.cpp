#include "pch.h"
#include "UIElementExtension.h"
#if __has_include("UIElementExtension.g.cpp")
#include "UIElementExtension.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Composition.h>

namespace winrt::UWPPackage::implementation
{
    winrt::Windows::UI::Xaml::DependencyProperty UIElementExtension::s_clipToBoundsProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"ClipToBounds",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{ nullptr, &UIElementExtension::onClipToBoundsPropertyChanged }
    );
    winrt::Windows::UI::Xaml::DependencyProperty UIElementExtension::ClipToBoundsProperty()
    {
        return s_clipToBoundsProperty;
    }
    bool UIElementExtension::GetClipToBounds(winrt::Windows::UI::Xaml::UIElement element)
    {
        return winrt::unbox_value<bool>(element.GetValue(s_clipToBoundsProperty));
    }
    void UIElementExtension::SetClipToBounds(winrt::Windows::UI::Xaml::UIElement element, bool value)
    {
        element.SetValue(s_clipToBoundsProperty, winrt::box_value(value));
    }

    void UIElementExtension::onClipToBoundsPropertyChanged(
        winrt::Windows::UI::Xaml::DependencyObject d,
        winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto element = d.try_as<winrt::Windows::UI::Xaml::UIElement>())
        {
            auto const value = winrt::unbox_value<bool>(e.NewValue());
            auto visual = winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(element);
            visual.Clip(value ? visual.Compositor().CreateInsetClip() : nullptr);
        }
    }
}

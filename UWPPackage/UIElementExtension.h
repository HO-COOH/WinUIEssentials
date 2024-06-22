#pragma once

#include "UIElementExtension.g.h"

namespace winrt::UWPPackage::implementation
{
    struct UIElementExtension : UIElementExtensionT<UIElementExtension>
    {
        UIElementExtension() = default;

        static winrt::Windows::UI::Xaml::DependencyProperty ClipToBoundsProperty();
        static bool GetClipToBounds(winrt::Windows::UI::Xaml::UIElement element);
        static void SetClipToBounds(winrt::Windows::UI::Xaml::UIElement element, bool value);
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_clipToBoundsProperty;
        static void onClipToBoundsPropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct UIElementExtension : UIElementExtensionT<UIElementExtension, implementation::UIElementExtension>
    {
    };
}

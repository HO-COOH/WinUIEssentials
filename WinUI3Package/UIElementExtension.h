#pragma once

#include "UIElementExtension.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct UIElementExtension : UIElementExtensionT<UIElementExtension>
    {
        UIElementExtension() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty ClipToBoundsProperty();
        static bool GetClipToBounds(winrt::Microsoft::UI::Xaml::UIElement element);
        static void SetClipToBounds(winrt::Microsoft::UI::Xaml::UIElement element, bool value);
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_clipToBoundsProperty;
        static void onClipToBoundsPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct UIElementExtension : UIElementExtensionT<UIElementExtension, implementation::UIElementExtension>
    {
    };
}

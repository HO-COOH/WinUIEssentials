#pragma once

#include "UIElementExtension.g.h"

namespace winrt::PackageRoot::implementation
{
    struct UIElementExtension
    {
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ClipToBoundsProperty();
        static bool GetClipToBounds(winrt::WinUINamespace::UI::Xaml::UIElement const& element);
        static void SetClipToBounds(winrt::WinUINamespace::UI::Xaml::UIElement const& element, bool value);
    private:
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_clipToBoundsProperty;
        static void onClipToBoundsPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct UIElementExtension : UIElementExtensionT<UIElementExtension, implementation::UIElementExtension>
    {
    };
}

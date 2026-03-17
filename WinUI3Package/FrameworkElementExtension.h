#pragma once
#include "FrameworkElementExtension.g.h"
#include <unordered_map>

namespace winrt::WinUI3Package::implementation
{
    struct FrameworkElementExtension : FrameworkElementExtensionT<FrameworkElementExtension>
    {
        static winrt::Windows::UI::Xaml::Interop::TypeName GetAncestorType(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);
        static void SetAncestorType(winrt::Microsoft::UI::Xaml::FrameworkElement const& element, winrt::Windows::UI::Xaml::Interop::TypeName const& type);
        static winrt::Microsoft::UI::Xaml::DependencyProperty AncestorTypeProperty();

        static winrt::Windows::Foundation::IInspectable GetAncestor(winrt::Microsoft::UI::Xaml::DependencyObject const& obj);
        static void SetAncestor(winrt::Microsoft::UI::Xaml::DependencyObject const& obj, winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty AncestorProperty();

    private:
        static void onAncestorTypeChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_ancestorTypeProperty{ nullptr };
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_ancestorProperty{ nullptr };

        static void ensureProperties();
        static void onElementLoaded(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);

        static inline std::unordered_map<void*, winrt::event_token> s_loadedTokens;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct FrameworkElementExtension : FrameworkElementExtensionT<FrameworkElementExtension, implementation::FrameworkElementExtension>
    {
    };
}

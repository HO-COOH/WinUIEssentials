#include "pch.h"
#include "UIElementExtension.h"
#if __has_include("UIElementExtension.g.cpp")
#include "UIElementExtension.g.cpp"
#endif

#if defined Build_WinUIPackage
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#else
#include <winrt/Windows.UI.Xaml.Hosting.h>
#endif

namespace winrt::PackageRoot::implementation
{
    winrt::WinUINamespace::UI::Xaml::DependencyProperty UIElementExtension::s_clipToBoundsProperty =
        winrt::WinUINamespace::UI::Xaml::DependencyProperty::RegisterAttached(
            L"ClipToBounds",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<winrt::PackageRoot::UIElementExtension>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &UIElementExtension::onClipToBoundsPropertyChanged }
        );

    winrt::WinUINamespace::UI::Xaml::DependencyProperty UIElementExtension::ClipToBoundsProperty()
    {
		return s_clipToBoundsProperty;
	}

    bool UIElementExtension::GetClipToBounds(winrt::WinUINamespace::UI::Xaml::UIElement const& element)
    {
        return winrt::unbox_value<bool>(element.GetValue(s_clipToBoundsProperty));
    }

    void UIElementExtension::SetClipToBounds(winrt::WinUINamespace::UI::Xaml::UIElement const& element, bool value)
    {
        element.SetValue(s_clipToBoundsProperty, winrt::box_value(value));
    }

    void UIElementExtension::onClipToBoundsPropertyChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto element = d.try_as<winrt::WinUINamespace::UI::Xaml::UIElement>())
        {
            auto const value = winrt::unbox_value<bool>(e.NewValue());
            auto visual = winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(element);
            visual.Clip(value ? visual.Compositor().CreateInsetClip() : nullptr);
        }
    }
}

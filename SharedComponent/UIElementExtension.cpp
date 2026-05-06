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
    winrt::WinUINamespace::UI::Xaml::DependencyProperty UIElementExtension::ClipToBoundsProperty()
    {
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_clipToBoundsProperty = 
			winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
					L"ClipToBounds",
					winrt::xaml_typename<bool>(),
					winrt::xaml_typename<class_type>(),
					winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &UIElementExtension::onClipToBoundsPropertyChanged }
		);
		return s_clipToBoundsProperty;
	}
    bool UIElementExtension::GetClipToBounds(winrt::WinUINamespace::UI::Xaml::UIElement element)
    {
        return winrt::unbox_value<bool>(element.GetValue(ClipToBoundsProperty()));
    }
    void UIElementExtension::SetClipToBounds(winrt::WinUINamespace::UI::Xaml::UIElement element, bool value)
    {
        element.SetValue(ClipToBoundsProperty(), winrt::box_value(value));
    }

    void UIElementExtension::onClipToBoundsPropertyChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject d, 
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

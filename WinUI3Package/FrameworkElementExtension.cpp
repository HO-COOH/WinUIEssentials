#include "pch.h"
#include "FrameworkElementExtension.h"
#if __has_include("FrameworkElementExtension.g.cpp")
#include "FrameworkElementExtension.g.cpp"
#endif
using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::WinUI3Package::implementation
{
    winrt::Windows::UI::Xaml::Interop::TypeName FrameworkElementExtension::GetAncestorType(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
    {
        return winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(element.GetValue(AncestorTypeProperty()));
    }
    
    void FrameworkElementExtension::SetAncestorType(winrt::Microsoft::UI::Xaml::FrameworkElement const& element, winrt::Windows::UI::Xaml::Interop::TypeName const& type)
    {
        element.SetValue(AncestorTypeProperty(), winrt::box_value(type));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty FrameworkElementExtension::AncestorTypeProperty()
    {
        return s_ancestorTypeProperty;
    }

    winrt::Windows::Foundation::IInspectable FrameworkElementExtension::GetAncestor(winrt::Microsoft::UI::Xaml::DependencyObject const& obj)
    {
        return obj.GetValue(AncestorProperty());
    }

    void FrameworkElementExtension::SetAncestor(winrt::Microsoft::UI::Xaml::DependencyObject const& obj, winrt::Windows::Foundation::IInspectable const& value)
    {
        obj.SetValue(AncestorProperty(), value);
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty FrameworkElementExtension::AncestorProperty()
    {
        return s_ancestorProperty;
    }

    void FrameworkElementExtension::onAncestorTypeChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
    {
        auto frameworkElement = d.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
        if (!frameworkElement)
            return;

        auto newValue = arg.NewValue();
        if (!newValue)
            return;

        auto abi = winrt::get_abi(frameworkElement);
        if (auto iter = s_loadedTokens.find(abi); iter != s_loadedTokens.end())
        {
            frameworkElement.Loaded(iter->second);
            s_loadedTokens.erase(iter);
        }

        //s_loadedTokens.try_emplace(abi, frameworkElement.Loaded([/*type = winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(newValue)*/](auto&& self, auto&&) {
        //    //auto frameworkElement = self.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
        //    //auto parent = frameworkElement.Parent();
        //    //while (parent && winrt::get_class_name(parent) != type.Name)
        //    //{
        //    //    if (auto element = parent.as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
        //    //        parent = element.Parent();
        //    //    else
        //    //        parent = nullptr;
        //    //}

        //    //SetAncestor(frameworkElement, parent);
        //}));

        if (auto parent = frameworkElement.Parent())
        {

        }
    }

    void FrameworkElementExtension::ensureProperties()
    {
        if (s_ancestorTypeProperty)
            return;

        s_ancestorTypeProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"AncestorType",
            winrt::xaml_typename<winrt::Windows::UI::Xaml::Interop::TypeName>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &FrameworkElementExtension::onAncestorTypeChanged }
        );
        s_ancestorProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"Ancestor",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<class_type>(),
            nullptr
        );
    }
}

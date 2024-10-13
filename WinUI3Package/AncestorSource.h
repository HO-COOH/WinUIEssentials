#pragma once

#include "AncestorSource.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct AncestorSource : AncestorSourceT<AncestorSource>
    {
        AncestorSource() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty AncestorTypeProperty()
        {
            return s_ancestorTypeProperty;
        }

        static void SetAncestorType(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element,
            winrt::Windows::UI::Xaml::Interop::TypeName const& value
        )
        {
            element.SetValue(AncestorTypeProperty(), winrt::box_value(value));
        }

        static winrt::Windows::UI::Xaml::Interop::TypeName GetAncestorType(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element
        )
        {
            return winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(element.GetValue(AncestorTypeProperty()));
        }

    private:
        static winrt::Windows::Foundation::IInspectable findParent(
            winrt::Microsoft::UI::Xaml::DependencyObject const& obj,
            winrt::Windows::UI::Xaml::Interop::TypeName const& typeName
        )
        {
            if (auto parent = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetParent(obj); parent)
            {
                if (typeName.Name == winrt::get_class_name(parent)) //this returns a fully-qualified value, so does not work in C++winrt
                    return parent;
                return findParent(parent, typeName);
            }

            return nullptr;
                
        }

        static void onAncestorTypeChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        )
        {
            auto target = d.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
            auto targetType = GetAncestorType(target);
            if (!targetType.Name.empty())
            {
                target.Loaded([target, targetType](winrt::Windows::Foundation::IInspectable const& sender, auto&&)
                    {
                        target.DataContext(findParent(target, targetType));
                    });
                
            }
        }
        inline static winrt::Microsoft::UI::Xaml::DependencyProperty s_ancestorTypeProperty =
            winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
                L"AncestorType",
                winrt::xaml_typename<winrt::Windows::UI::Xaml::Interop::TypeName>(),
                winrt::xaml_typename<class_type>(),
                winrt::Microsoft::UI::Xaml::PropertyMetadata{
                    nullptr,
                    &AncestorSource::onAncestorTypeChanged
                }
            );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct AncestorSource : AncestorSourceT<AncestorSource, implementation::AncestorSource>
    {
    };
}

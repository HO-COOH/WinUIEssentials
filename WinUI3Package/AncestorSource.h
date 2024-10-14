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
            winrt::hstring const& value
        )
        {
            element.SetValue(AncestorTypeProperty(), winrt::box_value(value));
        }

        static winrt::hstring GetAncestorType(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element
        )
        {
            return winrt::unbox_value<winrt::hstring>(element.GetValue(AncestorTypeProperty()));
        }


#pragma region Ancestor
        static winrt::Microsoft::UI::Xaml::DependencyProperty AncestorProperty()
        {
            return s_ancestorProperty;
        }

        static void SetAncestor(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element,
            winrt::Windows::Foundation::IInspectable const& value
        )
        {
            element.SetValue(AncestorProperty(), value);
        }

        static winrt::Windows::Foundation::IInspectable GetAncestor(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element
        )
        {
            return element.GetValue(AncestorProperty());
        }
#pragma endregion

    private:
        static winrt::Windows::Foundation::IInspectable findParent(
            winrt::Microsoft::UI::Xaml::DependencyObject const& obj,
            winrt::hstring const& name
        )
        {
            if (auto parent = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetParent(obj); parent)
            {
                for (auto i = 0; i < winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(parent); ++i)
                {
               
                    if (auto child = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(parent, i); child.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().Name() == name)
                        return child;
                }

                return findParent(parent, name);
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
            if (!targetType.empty())
            {
                if (target.IsLoaded())
                    SetAncestor(target, findParent(target, targetType));
                else
                    target.Loaded([target, targetType](winrt::Windows::Foundation::IInspectable const& sender, auto&&)
                        {
                           SetAncestor(target, findParent(target, targetType));
                        });
                
            }
        }
        inline static winrt::Microsoft::UI::Xaml::DependencyProperty s_ancestorTypeProperty =
            winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
                L"AncestorType",
                winrt::xaml_typename<winrt::hstring>(),
                winrt::xaml_typename<class_type>(),
                winrt::Microsoft::UI::Xaml::PropertyMetadata{
                    nullptr,
                    &AncestorSource::onAncestorTypeChanged
                }
            );

        inline static winrt::Microsoft::UI::Xaml::DependencyProperty s_ancestorProperty =
            winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
                L"Ancestor",
                winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
                winrt::xaml_typename<class_type>(),
                nullptr
            );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct AncestorSource : AncestorSourceT<AncestorSource, implementation::AncestorSource>
    {
    };
}

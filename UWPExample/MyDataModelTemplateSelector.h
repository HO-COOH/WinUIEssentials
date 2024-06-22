#pragma once

#include "MyDataModelTemplateSelector.g.h"

namespace winrt::UWPExample::implementation
{
    struct MyDataModelTemplateSelector : MyDataModelTemplateSelectorT<MyDataModelTemplateSelector>
    {
        MyDataModelTemplateSelector() = default;

        winrt::Windows::UI::Xaml::DataTemplate ButtonTemplate();
        void ButtonTemplate(winrt::Windows::UI::Xaml::DataTemplate value);

        winrt::Windows::UI::Xaml::DataTemplate LinkButtonTemplate();
        void LinkButtonTemplate(winrt::Windows::UI::Xaml::DataTemplate value);

        winrt::Windows::UI::Xaml::DataTemplate NoButtonTemplate();
        void NoButtonTemplate(winrt::Windows::UI::Xaml::DataTemplate value);

        winrt::Windows::UI::Xaml::DataTemplate SelectTemplateCore(
            winrt::Windows::Foundation::IInspectable item
        );

        winrt::Windows::UI::Xaml::DataTemplate SelectTemplateCore(
            winrt::Windows::Foundation::IInspectable item,
            winrt::Windows::UI::Xaml::DependencyObject container
        )
        {
            return SelectTemplateCore(item);
        }
    private:
        winrt::Windows::UI::Xaml::DataTemplate m_buttonTemplate{ nullptr };
        winrt::Windows::UI::Xaml::DataTemplate m_linkButtonTemplate{ nullptr };
        winrt::Windows::UI::Xaml::DataTemplate m_noButtonTemplate{ nullptr };
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct MyDataModelTemplateSelector : MyDataModelTemplateSelectorT<MyDataModelTemplateSelector, implementation::MyDataModelTemplateSelector>
    {
    };
}

#pragma once

#include "MyDataModelTemplateSelector.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MyDataModelTemplateSelector : MyDataModelTemplateSelectorT<MyDataModelTemplateSelector>
    {
        MyDataModelTemplateSelector() = default;

        winrt::Microsoft::UI::Xaml::DataTemplate ButtonTemplate();
        void ButtonTemplate(winrt::Microsoft::UI::Xaml::DataTemplate value);

        winrt::Microsoft::UI::Xaml::DataTemplate LinkButtonTemplate();
        void LinkButtonTemplate(winrt::Microsoft::UI::Xaml::DataTemplate value);

        winrt::Microsoft::UI::Xaml::DataTemplate NoButtonTemplate();
        void NoButtonTemplate(winrt::Microsoft::UI::Xaml::DataTemplate value);

        winrt::Microsoft::UI::Xaml::DataTemplate SelectTemplateCore(
            winrt::Windows::Foundation::IInspectable item
        );

        winrt::Microsoft::UI::Xaml::DataTemplate SelectTemplateCore(
            winrt::Windows::Foundation::IInspectable item,
            winrt::Microsoft::UI::Xaml::DependencyObject container
        )
        {
            return SelectTemplateCore(item);
        }
    private:
        winrt::Microsoft::UI::Xaml::DataTemplate m_buttonTemplate{ nullptr };
        winrt::Microsoft::UI::Xaml::DataTemplate m_linkButtonTemplate{ nullptr };
        winrt::Microsoft::UI::Xaml::DataTemplate m_noButtonTemplate{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MyDataModelTemplateSelector : MyDataModelTemplateSelectorT<MyDataModelTemplateSelector, implementation::MyDataModelTemplateSelector>
    {
    };
}

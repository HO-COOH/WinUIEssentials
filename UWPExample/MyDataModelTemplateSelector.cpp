#include "pch.h"
#include "MyDataModelTemplateSelector.h"
#if __has_include("MyDataModelTemplateSelector.g.cpp")
#include "MyDataModelTemplateSelector.g.cpp"
#endif
#include "MyDataModel.g.h"

namespace winrt::UWPExample::implementation
{
    winrt::Windows::UI::Xaml::DataTemplate MyDataModelTemplateSelector::ButtonTemplate()
    {
        return m_buttonTemplate;
    }
    void MyDataModelTemplateSelector::ButtonTemplate(winrt::Windows::UI::Xaml::DataTemplate value)
    {
        m_buttonTemplate = value;
    }
    winrt::Windows::UI::Xaml::DataTemplate MyDataModelTemplateSelector::LinkButtonTemplate()
    {
        return m_linkButtonTemplate;
    }
    void MyDataModelTemplateSelector::LinkButtonTemplate(winrt::Windows::UI::Xaml::DataTemplate value)
    {
        m_linkButtonTemplate = value;
    }
    winrt::Windows::UI::Xaml::DataTemplate MyDataModelTemplateSelector::NoButtonTemplate()
    {
        return m_noButtonTemplate;
    }
    void MyDataModelTemplateSelector::NoButtonTemplate(winrt::Windows::UI::Xaml::DataTemplate value)
    {
        m_noButtonTemplate = value;
    }
    winrt::Windows::UI::Xaml::DataTemplate MyDataModelTemplateSelector::SelectTemplateCore(winrt::Windows::Foundation::IInspectable item)
    {
        auto itm = item.as<UWPExample::MyDataModel>();
        if (itm.ItemType().ends_with(L"Button"))
            return ButtonTemplate();
        else if (itm.ItemType().ends_with(L"Link button"))
            return LinkButtonTemplate();
        else
            return NoButtonTemplate();
    }
}

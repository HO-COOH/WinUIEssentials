#include "pch.h"
#include "MyDataModelTemplateSelector.h"
#if __has_include("MyDataModelTemplateSelector.g.cpp")
#include "MyDataModelTemplateSelector.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    winrt::Microsoft::UI::Xaml::DataTemplate MyDataModelTemplateSelector::ButtonTemplate()
    {
        return m_buttonTemplate;
    }
    void MyDataModelTemplateSelector::ButtonTemplate(winrt::Microsoft::UI::Xaml::DataTemplate value)
    {
        m_buttonTemplate = value;
    }
    winrt::Microsoft::UI::Xaml::DataTemplate MyDataModelTemplateSelector::LinkButtonTemplate()
    {
        return m_linkButtonTemplate;
    }
    void MyDataModelTemplateSelector::LinkButtonTemplate(winrt::Microsoft::UI::Xaml::DataTemplate value)
    {
        m_linkButtonTemplate = value;
    }
    winrt::Microsoft::UI::Xaml::DataTemplate MyDataModelTemplateSelector::NoButtonTemplate()
    {
        return m_noButtonTemplate;
    }
    void MyDataModelTemplateSelector::NoButtonTemplate(winrt::Microsoft::UI::Xaml::DataTemplate value)
    {
        m_noButtonTemplate = value;
    }
    winrt::Microsoft::UI::Xaml::DataTemplate MyDataModelTemplateSelector::SelectTemplateCore(winrt::Windows::Foundation::IInspectable item)
    {
        auto itm = item.as<WinUI3Example::MyDataModel>();
        if (itm.ItemType().ends_with(L"Button"))
            return ButtonTemplate();
        else if (itm.ItemType().ends_with(L"Link button"))
            return LinkButtonTemplate();
        else
            return NoButtonTemplate();
    }
}

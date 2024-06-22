#include "pch.h"
#include "MyDataModel.h"
#if __has_include("MyDataModel.g.cpp")
#include "MyDataModel.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
    winrt::hstring MyDataModel::Name()
    {
        return m_name;
    }
    void MyDataModel::Name(winrt::hstring value)
    {
        m_name = value;
    }
    winrt::hstring MyDataModel::Info()
    {
        return m_info;
    }
    void MyDataModel::Info(winrt::hstring value)
    {
        m_info = value;
    }
    winrt::hstring MyDataModel::ItemType()
    {
        return m_itemType;
    }
    void MyDataModel::ItemType(winrt::hstring value)
    {
        m_itemType = value;
    }
    winrt::hstring MyDataModel::LinkDescription()
    {
        return m_linkDescription;
    }
    void MyDataModel::LinkDescription(winrt::hstring value)
    {
        m_linkDescription = value;
    }
    winrt::hstring MyDataModel::Url()
    {
        return m_url;
    }
    void MyDataModel::Url(winrt::hstring value)
    {
        m_url = value;
    }
}

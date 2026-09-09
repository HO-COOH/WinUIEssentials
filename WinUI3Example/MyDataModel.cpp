#include "pch.h"
#include "MyDataModel.h"
#if __has_include("MyDataModel.g.cpp")
#include "MyDataModel.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    MyDataModel::MyDataModel(
        winrt::hstring const& name,
        winrt::hstring const& info,
        winrt::hstring const& itemType,
        winrt::hstring const& linkDescription,
        winrt::hstring const& url) :
        m_name{name},
		m_info{ info },
		m_itemType{ itemType },
		m_linkDescription{ linkDescription },
		m_url{ url }
    {
    }

    winrt::hstring MyDataModel::Name()
    {
        return m_name;
    }

    winrt::hstring MyDataModel::Info()
    {
        return m_info;
    }

    winrt::hstring MyDataModel::ItemType()
    {
        return m_itemType;
    }

    winrt::hstring MyDataModel::LinkDescription()
    {
        return m_linkDescription;
    }

    winrt::hstring MyDataModel::Url()
    {
        return m_url;
    }
}

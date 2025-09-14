#include "pch.h"
#include "ContributorItem.h"
#if __has_include("ContributorItem.g.cpp")
#include "ContributorItem.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    ContributorItem::ContributorItem(
        winrt::hstring name, 
        winrt::Windows::Foundation::Uri avator, 
        winrt::Windows::Foundation::Uri profile) : m_name{ name }, m_avator{ avator }, m_profile{ profile }
    {
    }

    ContributorItem::ContributorItem(winrt::Windows::Data::Json::JsonObject const& json) :
        m_name{ json.GetNamedString(L"login") },
        m_avator{ winrt::Windows::Foundation::Uri{ json.GetNamedString(L"avatar_url") } },
        m_profile{ winrt::Windows::Foundation::Uri{ json.GetNamedString(L"html_url") } }
    {
    }

    winrt::hstring ContributorItem::Name()
    {
        return m_name;
	}

    winrt::Windows::Foundation::Uri ContributorItem::Avator()
    {
        return m_avator;
    }

    winrt::Windows::Foundation::Uri ContributorItem::Profile()
    {
        return m_profile;
    }
}

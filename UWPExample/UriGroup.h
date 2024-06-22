#pragma once

#include "UriGroup.g.h"

namespace winrt::UWPExample::implementation
{
    struct UriGroup : UriGroupT<UriGroup>
    {
        UriGroup(
            winrt::hstring title,
            winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> uris
        ) :m_title{ title }, m_uris{ uris }
        {}

        winrt::hstring Title() { return m_title; }
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Uris() { return m_uris; }
    private:
        winrt::hstring m_title;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_uris;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct UriGroup : UriGroupT<UriGroup, implementation::UriGroup>
    {
    };
}

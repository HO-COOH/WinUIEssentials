#pragma once

#include "UriModel.g.h"

namespace winrt::UWPExample::implementation
{
    struct UriModel : UriModelT<UriModel>
    {
        UriModel(winrt::hstring name, winrt::Windows::Foundation::Uri uri)
            : m_name{ name },
            m_uri{ uri }
        {
        }

        winrt::hstring Name() { return m_name; }
        winrt::Windows::Foundation::Uri Uri() { return m_uri; }
    private:
        winrt::hstring m_name;
        winrt::Windows::Foundation::Uri m_uri;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct UriModel : UriModelT<UriModel, implementation::UriModel>
    {
    };
}

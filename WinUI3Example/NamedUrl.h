#pragma once

#include "NamedUrl.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct NamedUrl : NamedUrlT<NamedUrl>
    {
        NamedUrl() = default;

        winrt::hstring Name();
		void Name(winrt::hstring const& value);

        winrt::Windows::Foundation::Uri Url();
		void Url(winrt::Windows::Foundation::Uri const& value);

    private:
        winrt::hstring m_name;
        winrt::Windows::Foundation::Uri m_url{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct NamedUrl : NamedUrlT<NamedUrl, implementation::NamedUrl>
    {
    };
}

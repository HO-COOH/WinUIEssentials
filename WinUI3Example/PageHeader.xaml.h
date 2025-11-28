#pragma once

#include "PageHeader.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct PageHeader : PageHeaderT<PageHeader>
    {
        PageHeader() = default;

        winrt::hstring Header();
        void Header(winrt::hstring const& value);

        winrt::hstring Description();
        void Description(winrt::hstring const& value);

        winrt::Windows::Foundation::Uri SampleUrl();
        void SampleUrl(winrt::Windows::Foundation::Uri const& value);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Urls();

    private:
        winrt::hstring m_header;
        winrt::hstring m_description;
        winrt::Windows::Foundation::Uri m_sampleUrl{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_urls{ winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>() };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct PageHeader : PageHeaderT<PageHeader, implementation::PageHeader>
    {
    };
}

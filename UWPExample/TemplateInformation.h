#pragma once

#include "TemplateInformation.g.h"

namespace winrt::UWPExample::implementation
{
    struct TemplateInformation : TemplateInformationT<TemplateInformation>
    {
        TemplateInformation() = default;

        winrt::hstring Header1();
        void Header1(winrt::hstring const& value);

        winrt::hstring Regex1();
        void Regex1(winrt::hstring const& value);

        winrt::hstring PlaceholderText1();
        void PlaceholderText1(winrt::hstring const& value);

    private:
        winrt::hstring m_header;
        winrt::hstring m_regex;
        winrt::hstring m_placeholderText;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TemplateInformation : TemplateInformationT<TemplateInformation, implementation::TemplateInformation>
    {
    };
}

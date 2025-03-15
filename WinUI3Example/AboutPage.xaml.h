#pragma once

#include "AboutPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct AboutPage : AboutPageT<AboutPage>
    {
        AboutPage() = default;

        static winrt::hstring WASDKReleaseVersion();
        static winrt::hstring WASDKRuntimeVersion();
        static winrt::hstring FormatVersion(
            uint32_t major,
            uint32_t minor,
            uint32_t patch,
            uint32_t majorMinor,
            winrt::hstring const& channel
        );
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AboutPage : AboutPageT<AboutPage, implementation::AboutPage>
    {
    };
}

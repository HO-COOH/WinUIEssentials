#pragma once

#include "FontIconExtensionPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct FontIconExtensionPage : FontIconExtensionPageT<FontIconExtensionPage>
    {
        FontIconExtensionPage() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct FontIconExtensionPage : FontIconExtensionPageT<FontIconExtensionPage, implementation::FontIconExtensionPage>
    {
    };
}

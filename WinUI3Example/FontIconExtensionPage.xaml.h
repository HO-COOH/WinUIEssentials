#pragma once

#include "FontIconExtensionPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct FontIconExtensionPage : FontIconExtensionPageT<FontIconExtensionPage>
    {
        FontIconExtensionPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FontIconExtensionPage : FontIconExtensionPageT<FontIconExtensionPage, implementation::FontIconExtensionPage>
    {
    };
}

// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "GlyphsPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct GlyphsPage : GlyphsPageT<GlyphsPage>
    {
        GlyphsPage() = default;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Glyphs();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct GlyphsPage : GlyphsPageT<GlyphsPage, implementation::GlyphsPage>
    {
    };
}

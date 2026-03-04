// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MarqueeTextPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MarqueeTextPage : MarqueeTextPageT<MarqueeTextPage>
    {
        MarqueeTextPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MarqueeTextPage : MarqueeTextPageT<MarqueeTextPage, implementation::MarqueeTextPage>
    {
    };
}

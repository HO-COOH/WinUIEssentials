// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MarqueeTextPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MarqueeTextPage : MarqueeTextPageT<MarqueeTextPage>
    {
        MarqueeTextPage() = default;

        static WinUI3Package::MarqueeBehavior GetBehaviorFromIndex(int value);
        static WinUI3Package::MarqueeDirection GetDirectionFromIndex(int value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MarqueeTextPage : MarqueeTextPageT<MarqueeTextPage, implementation::MarqueeTextPage>
    {
    };
}

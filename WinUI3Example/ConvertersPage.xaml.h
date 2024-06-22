// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "ConvertersPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ConvertersPage : ConvertersPageT<ConvertersPage>
    {
        ConvertersPage();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ConvertersPage : ConvertersPageT<ConvertersPage, implementation::ConvertersPage>
    {
    };
}

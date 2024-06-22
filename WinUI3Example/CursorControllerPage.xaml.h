// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "CursorControllerPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CursorControllerPage : CursorControllerPageT<CursorControllerPage>
    {
        CursorControllerPage();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CursorControllerPage : CursorControllerPageT<CursorControllerPage, implementation::CursorControllerPage>
    {
    };
}

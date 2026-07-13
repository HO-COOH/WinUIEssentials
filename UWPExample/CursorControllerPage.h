#pragma once

#include "CursorControllerPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct CursorControllerPage : CursorControllerPageT<CursorControllerPage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct CursorControllerPage : CursorControllerPageT<CursorControllerPage, implementation::CursorControllerPage>
    {
    };
}

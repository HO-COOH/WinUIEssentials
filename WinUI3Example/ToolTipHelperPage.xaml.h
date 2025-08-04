#pragma once

#include "ToolTipHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ToolTipHelperPage : ToolTipHelperPageT<ToolTipHelperPage>
    {
        ToolTipHelperPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ToolTipHelperPage : ToolTipHelperPageT<ToolTipHelperPage, implementation::ToolTipHelperPage>
    {
    };
}

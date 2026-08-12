#pragma once

#include "CommandBarHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CommandBarHelperPage : CommandBarHelperPageT<CommandBarHelperPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CommandBarHelperPage : CommandBarHelperPageT<CommandBarHelperPage, implementation::CommandBarHelperPage>
    {
    };
}

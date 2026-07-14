#pragma once

#include "DefaultTableContextMenu.g.h"

namespace winrt::PackageRoot::implementation
{
    struct DefaultTableContextMenu : DefaultTableContextMenuT<DefaultTableContextMenu>
    {
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct DefaultTableContextMenu : DefaultTableContextMenuT<DefaultTableContextMenu, implementation::DefaultTableContextMenu>
    {
    };
}

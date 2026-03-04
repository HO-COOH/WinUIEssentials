#pragma once

#include "ModernDialogBoxContent_Resource.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ModernDialogBoxContent_Resource : ModernDialogBoxContent_ResourceT<ModernDialogBoxContent_Resource>
    {
        ModernDialogBoxContent_Resource() = default;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ModernDialogBoxContent_Resource : ModernDialogBoxContent_ResourceT<ModernDialogBoxContent_Resource, implementation::ModernDialogBoxContent_Resource>
    {
    };
}

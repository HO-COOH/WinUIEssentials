#pragma once

#include "SettingsCard_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SettingsCard_Resource : SettingsCard_ResourceT<SettingsCard_Resource>
    {
        SettingsCard_Resource() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsCard_Resource : SettingsCard_ResourceT<SettingsCard_Resource, implementation::SettingsCard_Resource>
    {
    };
}

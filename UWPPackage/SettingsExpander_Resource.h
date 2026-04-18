#pragma once

#include "SettingsExpander_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SettingsExpander_Resource : SettingsExpander_ResourceT<SettingsExpander_Resource>
    {
        SettingsExpander_Resource() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsExpander_Resource : SettingsExpander_ResourceT<SettingsExpander_Resource, implementation::SettingsExpander_Resource>
    {
    };
}

#pragma once

#include "SettingsExpander_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SettingsExpander_Resource : SettingsExpander_ResourceT<SettingsExpander_Resource>
    {
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsExpander_Resource : SettingsExpander_ResourceT<SettingsExpander_Resource, implementation::SettingsExpander_Resource>
    {
    };
}

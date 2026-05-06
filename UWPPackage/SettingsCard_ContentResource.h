#pragma once

#include "SettingsCard_ContentResource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SettingsCard_ContentResource : SettingsCard_ContentResourceT<SettingsCard_ContentResource>
    {
        SettingsCard_ContentResource() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsCard_ContentResource : SettingsCard_ContentResourceT<SettingsCard_ContentResource, implementation::SettingsCard_ContentResource>
    {
    };
}

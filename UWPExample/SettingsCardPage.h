#pragma once

#include "SettingsCardPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SettingsCardPage : SettingsCardPageT<SettingsCardPage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SettingsCardPage : SettingsCardPageT<SettingsCardPage, implementation::SettingsCardPage>
    {
    };
}

#pragma once

#include "SampleSettingsPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SampleSettingsPage : SampleSettingsPageT<SampleSettingsPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SampleSettingsPage : SampleSettingsPageT<SampleSettingsPage, implementation::SampleSettingsPage>
    {
    };
}

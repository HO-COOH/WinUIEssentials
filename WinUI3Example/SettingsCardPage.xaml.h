// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "SettingsCardPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SettingsCardPage : SettingsCardPageT<SettingsCardPage>
    {
        SettingsCardPage();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SettingsCardPage : SettingsCardPageT<SettingsCardPage, implementation::SettingsCardPage>
    {
    };
}

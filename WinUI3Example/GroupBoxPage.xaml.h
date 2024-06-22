// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "GroupBoxPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage>
    {
        GroupBoxPage();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage, implementation::GroupBoxPage>
    {
    };
}

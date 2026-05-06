#pragma once

#include "GroupBoxPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage>
    {
        GroupBoxPage() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage, implementation::GroupBoxPage>
    {
    };
}

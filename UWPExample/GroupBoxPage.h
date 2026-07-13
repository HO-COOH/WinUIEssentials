#pragma once

#include "GroupBoxPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage, implementation::GroupBoxPage>
    {
    };
}

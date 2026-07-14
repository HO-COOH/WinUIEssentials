#pragma once

#include "GroupBox_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct GroupBox_Resource : GroupBox_ResourceT<GroupBox_Resource>
    {
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct GroupBox_Resource : GroupBox_ResourceT<GroupBox_Resource, implementation::GroupBox_Resource>
    {
    };
}

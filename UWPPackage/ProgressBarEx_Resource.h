#pragma once

#include "ProgressBarEx_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct ProgressBarEx_Resource : ProgressBarEx_ResourceT<ProgressBarEx_Resource>
    {
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct ProgressBarEx_Resource : ProgressBarEx_ResourceT<ProgressBarEx_Resource, implementation::ProgressBarEx_Resource>
    {
    };
}

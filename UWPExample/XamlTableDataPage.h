#pragma once

#include "XamlTableDataPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct XamlTableDataPage : XamlTableDataPageT<XamlTableDataPage>
    {
        XamlTableDataPage() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct XamlTableDataPage : XamlTableDataPageT<XamlTableDataPage, implementation::XamlTableDataPage>
    {
    };
}

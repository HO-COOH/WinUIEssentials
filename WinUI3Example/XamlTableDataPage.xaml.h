#pragma once

#include "XamlTableDataPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct XamlTableDataPage : XamlTableDataPageT<XamlTableDataPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct XamlTableDataPage : XamlTableDataPageT<XamlTableDataPage, implementation::XamlTableDataPage>
    {
    };
}

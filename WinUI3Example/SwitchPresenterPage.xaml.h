#pragma once

#include "SwitchPresenterPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SwitchPresenterPage : SwitchPresenterPageT<SwitchPresenterPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SwitchPresenterPage : SwitchPresenterPageT<SwitchPresenterPage, implementation::SwitchPresenterPage>
    {
    };
}

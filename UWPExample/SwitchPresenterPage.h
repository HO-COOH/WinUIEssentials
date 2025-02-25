#pragma once

#include "SwitchPresenterPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SwitchPresenterPage : SwitchPresenterPageT<SwitchPresenterPage>
    {
        SwitchPresenterPage() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SwitchPresenterPage : SwitchPresenterPageT<SwitchPresenterPage, implementation::SwitchPresenterPage>
    {
    };
}

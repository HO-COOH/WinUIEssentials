#pragma once

#include "FlyoutHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct FlyoutHelperPage : FlyoutHelperPageT<FlyoutHelperPage>
    {
        FlyoutHelperPage() = default;

        static std::vector<winrt::Windows::Foundation::IInspectable> Components();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FlyoutHelperPage : FlyoutHelperPageT<FlyoutHelperPage, implementation::FlyoutHelperPage>
    {
    };
}

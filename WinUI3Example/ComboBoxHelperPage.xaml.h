#pragma once
#include "ComboBoxHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ComboBoxHelperPage : ComboBoxHelperPageT<ComboBoxHelperPage>
    {
        ComboBoxHelperPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ComboBoxHelperPage : ComboBoxHelperPageT<ComboBoxHelperPage, implementation::ComboBoxHelperPage>
    {
    };
}

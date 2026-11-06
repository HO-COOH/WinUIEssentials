#pragma once

#include "ColorPickerHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ColorPickerHelperPage : ColorPickerHelperPageT<ColorPickerHelperPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ColorPickerHelperPage : ColorPickerHelperPageT<ColorPickerHelperPage, implementation::ColorPickerHelperPage>
    {
    };
}

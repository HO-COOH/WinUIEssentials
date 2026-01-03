#pragma once

#include "UnderlaySystemBackdropOptions.g.h"

#include "include/cppwinrt_utils.h"

namespace winrt::WinUI3Package::implementation
{
    struct UnderlaySystemBackdropOptions : UnderlaySystemBackdropOptionsT<UnderlaySystemBackdropOptions>
    {
        UnderlaySystemBackdropOptions();


		DEFINE_PROPERTY(WinUI3Package::UnderlayCoverMode, CoverMode);
		DEFINE_PROPERTY(winrt::Microsoft::UI::Xaml::ScalarTransition, OpacityTransition);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct UnderlaySystemBackdropOptions : UnderlaySystemBackdropOptionsT<UnderlaySystemBackdropOptions, implementation::UnderlaySystemBackdropOptions>
    {
    };
}

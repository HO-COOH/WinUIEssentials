#pragma once

#include "UnderlaySmokeLayerOptions.g.h"
#include "include/cppwinrt_utils.h"

namespace winrt::WinUI3Package::implementation
{
    struct UnderlaySmokeLayerOptions : UnderlaySmokeLayerOptionsT<UnderlaySmokeLayerOptions>
    {
        UnderlaySmokeLayerOptions();


		DEFINE_PROPERTY(WinUI3Package::WindowedContentDialogSmokeLayerKind, SmokeLayerKind);
		DEFINE_PROPERTY2(Microsoft::UI::Xaml::UIElement, CustomSmokeLayer);
		DEFINE_PROPERTY(Microsoft::UI::Xaml::ScalarTransition, OpacityTransition);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct UnderlaySmokeLayerOptions : UnderlaySmokeLayerOptionsT<UnderlaySmokeLayerOptions, implementation::UnderlaySmokeLayerOptions>
    {
    };
}

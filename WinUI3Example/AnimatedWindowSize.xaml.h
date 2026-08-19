#pragma once

#include "AnimatedWindowSize.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct AnimatedWindowSize : AnimatedWindowSizeT<AnimatedWindowSize>
    {
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AnimatedWindowSize : AnimatedWindowSizeT<AnimatedWindowSize, implementation::AnimatedWindowSize>
    {
    };
}

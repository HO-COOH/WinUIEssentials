#pragma once

#include "EntranceAnimationDemo.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.UI.Composition.h>

namespace winrt::WinUI3Example::implementation
{
    struct EntranceAnimationDemo : EntranceAnimationDemoT<EntranceAnimationDemo>
    {
        constexpr static auto Width = 500;
        constexpr static auto Height = 200;
        constexpr static auto Radius = 20.f;
        EntranceAnimationDemo();

        void CreateVisual();
        winrt::Windows::UI::Composition::SpriteVisual createVisualW();
        void RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        static winrt::Windows::System::DispatcherQueueController s_queue;
        winrt::Microsoft::UI::Content::ContentExternalOutputLink externalOutputLink{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct EntranceAnimationDemo : EntranceAnimationDemoT<EntranceAnimationDemo, implementation::EntranceAnimationDemo>
    {
    };
}

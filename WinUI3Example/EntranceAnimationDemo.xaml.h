#pragma once

#include "EntranceAnimationDemo.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <DispatcherQueue.h>
#include <winrt/Windows.System.h>
#include <WindowsAppSDK-VersionInfo.h>

//forward declaration in case ContentExternalOutputLink not exist
namespace winrt::Microsoft::UI::Content
{
    struct ContentExternalOutputLink;
}
struct Dummy
{
    constexpr Dummy(std::nullptr_t) {}

    template<typename T>
    T as() { return T{}; }

    winrt::Microsoft::UI::Composition::Visual PlacementVisual() { return nullptr; }
};

//This function is only intended to be used with decltype(...)
//When ContentExternalOutputLink is available, it return its type,
//otherwise it returns int
constexpr auto CheckContentExternalOutputLinkFunc()
{
    if constexpr (std::string_view{ WINDOWSAPPSDK_RELEASE_CHANNEL } == "experimental")
    {
        winrt::Microsoft::UI::Content::ContentExternalOutputLink* ptr{ nullptr };
        return ptr;
    }
    else
    {
        Dummy* ptr{ nullptr };
        return ptr;
    }
}

namespace winrt::WinUI3Example::implementation
{
    winrt::Windows::System::DispatcherQueueController createSystemDispatcherQueueController();

    struct EntranceAnimationDemo : EntranceAnimationDemoT<EntranceAnimationDemo>
    {
        EntranceAnimationDemo();


        template<typename HasRadius>
        void CreateVisual(HasRadius const& element)
        {
            if constexpr (std::string_view{ WINDOWSAPPSDK_RELEASE_CHANNEL } == "experimental")
            {
                auto compositor = winrt::Microsoft::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread();
                externalOutputLink = winrt::Microsoft::UI::Content::ContentExternalOutputLink::Create(compositor);

                externalOutputLink.as<winrt::Windows::UI::Composition::CompositionTarget>().Root(createVisualW(element));
                auto placementVisual = externalOutputLink.PlacementVisual();
                placementVisual.Size(element.ActualSize());
                winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(AcrylicGrid(), placementVisual);
            }
        }

        void RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        static winrt::Windows::System::DispatcherQueueController s_queue;
        std::remove_reference_t<decltype(*CheckContentExternalOutputLinkFunc())> externalOutputLink{ nullptr };

        template<typename HasRadius>
        winrt::Windows::UI::Composition::SpriteVisual createVisualW(HasRadius const& element)
        {
            if (!winrt::Windows::System::DispatcherQueue::GetForCurrentThread())
                s_queue = createSystemDispatcherQueueController();

            winrt::Windows::UI::Composition::Compositor compositor;
            auto spriteVisual = compositor.CreateSpriteVisual();
            spriteVisual.Brush(compositor.CreateHostBackdropBrush());
            spriteVisual.Size(element.ActualSize());
            spriteVisual.BorderMode(winrt::Windows::UI::Composition::CompositionBorderMode::Soft);

            auto clip = compositor.CreateRoundedRectangleGeometry();
            auto cornerRadius = element.CornerRadius();
            clip.CornerRadius({ static_cast<float>(cornerRadius.TopLeft), static_cast<float>(cornerRadius.BottomRight) });
            clip.Size(spriteVisual.Size());

            spriteVisual.Clip(compositor.CreateGeometricClip(clip));

            return spriteVisual;
        }
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct EntranceAnimationDemo : EntranceAnimationDemoT<EntranceAnimationDemo, implementation::EntranceAnimationDemo>
    {
    };
}

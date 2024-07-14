#pragma once

#include "TransparentWindow.h"
#include "RoundedAnimatedAcrylicWindowWithShadow.g.h"


namespace winrt::WinUI3Package::implementation
{
    struct RoundedAnimatedAcrylicWindowWithShadow : winrt::Microsoft::UI::Xaml::Markup::ComponentConnectorT<RoundedAnimatedAcrylicWindowWithShadowT<RoundedAnimatedAcrylicWindowWithShadow>>
    {
        RoundedAnimatedAcrylicWindowWithShadow();

        winrt::Microsoft::UI::Xaml::CornerRadius CornerRadius();
        void CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadius const& value);

        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard EntranceStoryboard();
        void EntranceStoryboard(winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard const& value);

        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard ExitStoryboard();
        void ExitStoryboard(winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard const& value);

        winrt::Microsoft::UI::Xaml::UIElement WindowContent();
        void WindowContent(winrt::Microsoft::UI::Xaml::UIElement const& value);

        static winrt::Windows::Foundation::TimeSpan DurationToTimeSpan(winrt::Microsoft::UI::Xaml::Duration const& duration);
    private:
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard m_entranceStoryboard{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard m_exitStoryboard{ nullptr };
        winrt::Microsoft::UI::Xaml::CornerRadius m_cornerRadius{};
    public:
        winrt::Microsoft::UI::Composition::SpriteVisual m_shadowVisual{ nullptr };
        void ShadowElement_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RootGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct RoundedAnimatedAcrylicWindowWithShadow : RoundedAnimatedAcrylicWindowWithShadowT<RoundedAnimatedAcrylicWindowWithShadow, implementation::RoundedAnimatedAcrylicWindowWithShadow>
    {
    };
}

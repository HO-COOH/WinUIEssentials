#pragma once

#include "MarqueeText.g.h"
#include <winrt/Microsoft.UI.Xaml.Media.Animation.h>

namespace winrt::WinUI3Package::implementation
{
    struct MarqueeText : MarqueeTextT<MarqueeText>
    {
        MarqueeText() = default;

        void OnApplyTemplate();
            
        double Speed();
        void Speed(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty SpeedProperty();

        winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehavior RepeatBehavior();
        void RepeatBehavior(winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehavior value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty RepeatBehaviorProperty();

        WinUI3Package::MarqueeBehavior Behavior();
        void Behavior(WinUI3Package::MarqueeBehavior value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty BehaviorProperty();

        WinUI3Package::MarqueeDirection Direction();
        void Direction(WinUI3Package::MarqueeDirection value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty DirectionProperty();

        winrt::hstring Text();
        void Text(winrt::hstring value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TextProperty();

        bool PauseOnHover();
        void PauseOnHover(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty PauseOnHoverProperty();

        double IntervalSpace();
        void IntervalSpace(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IntervalSpaceProperty();

        void Pause();
        void Resume();
        void Reset();
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_speedProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_repeatBehaviorProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_behaviorProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_directionProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_textProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_pauseOnHoverProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_intervalSpaceProperty;

        //https://github.com/CommunityToolkit/Labs-Windows/blob/main/components/MarqueeText/src/MarqueeText.Properties.cs
        static void propertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void behaviorPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void directionPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void pauseOnHoverChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void spaceIntervalChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        winrt::event_token pointerEntered_revoker;
        winrt::event_token pointerExited_revoker;

        bool isHovering{};
        bool isPausing{};

        void resumeStoryboardImpl();

        constexpr static auto MarqueeTextPartName = L"MarqueeContainer";
        constexpr static auto Segment1PartName = L"Segment1";
        constexpr static auto Segment2PartName = L"Segment2";
        constexpr static auto MarqueeTransformPartName = L"MarqueeTransform";

        constexpr static auto MarqueeActiveState = L"MarqueeActive";
        constexpr static auto MarqueeStoppedState = L"MarqueeStopped";

        constexpr static auto DirectionVisualStateGroupName = L"DirectionStateGroup";
        constexpr static auto LeftwardsVisualStateName = L"Leftwards";
        constexpr static auto RightwardsVisualStateName = L"Rightwards";
        constexpr static auto UpwardsVisualStateName = L"Upwards";
        constexpr static auto DownwardsVisualStateName = L"Downwards";

        constexpr static auto BehaviorVisualStateGroupName = L"BehaviorStateGroup";
        constexpr static auto TickerVisualStateName = L"Ticker";
        constexpr static auto LoopingVisualStateName = L"Looping";
        constexpr static auto BouncingVisualStateName = L"Bouncing";

        winrt::Microsoft::UI::Xaml::FrameworkElement rootGrid{ nullptr };
        winrt::Microsoft::UI::Xaml::Controls::Panel marqueeContainer{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement segment1{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement segment2{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::TranslateTransform marqueeTransform{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard marqueeStoryboard{ nullptr };

        bool isActive{};
        void container_SizeChanged(winrt::Windows::Foundation::IInspectable sender,
            winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);

        constexpr static std::wstring_view getVisualStateName(MarqueeDirection direction);
        constexpr static std::wstring_view getVisualStateName(MarqueeBehavior behavior);

        void startMarquee();
        void stopMarquee(bool initialState);

        bool updateAnimation(bool resume);

        winrt::event<WinUI3Package::SignalDelegate> marqueeBegan;
        winrt::event<WinUI3Package::SignalDelegate> marqueeStopped;
        winrt::event<WinUI3Package::SignalDelegate> marqueeCompleted;

        winrt::event_token storyboardComplete_revoker;

        //bool isDirectionHorizontal();
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard createStoryboard(
            double start,
            double end,
            winrt::Windows::Foundation::TimeSpan duration,
            std::wstring_view targetProperty
        );
        void storyboard_completed(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::Foundation::IInspectable e
        );
        static bool isHorizontal(MarqueeDirection direction);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct MarqueeText : MarqueeTextT<MarqueeText, implementation::MarqueeText>
    {
    };
}

#pragma once

#include "MarqueeText.g.h"
#include "include/TemplateControlHelper.hpp"
#include <winrt/Windows.UI.Xaml.Media.Animation.h>


namespace winrt::UWPPackage::implementation
{
    struct MarqueeText : MarqueeTextT<MarqueeText>, TemplateControlHelper<MarqueeText>
    {
        MarqueeText() = default;

        void OnApplyTemplate();

        double Speed();
        void Speed(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty SpeedProperty();

        winrt::Windows::UI::Xaml::Media::Animation::RepeatBehavior RepeatBehavior();
        void RepeatBehavior(winrt::Windows::UI::Xaml::Media::Animation::RepeatBehavior value);
        static winrt::Windows::UI::Xaml::DependencyProperty RepeatBehaviorProperty();

        UWPPackage::MarqueeBehavior Behavior();
        void Behavior(UWPPackage::MarqueeBehavior value);
        static winrt::Windows::UI::Xaml::DependencyProperty BehaviorProperty();

        UWPPackage::MarqueeDirection Direction();
        void Direction(UWPPackage::MarqueeDirection value);
        static winrt::Windows::UI::Xaml::DependencyProperty DirectionProperty();

        winrt::hstring Text();
        void Text(winrt::hstring value);
        static winrt::Windows::UI::Xaml::DependencyProperty TextProperty();

        bool PauseOnHover();
        void PauseOnHover(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty PauseOnHoverProperty();

        double IntervalSpace();
        void IntervalSpace(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty IntervalSpaceProperty();

        void Pause();
        void Resume();
        void Reset();
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_speedProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_repeatBehaviorProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_behaviorProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_directionProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_textProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_pauseOnHoverProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_intervalSpaceProperty;

        //https://github.com/CommunityToolkit/Labs-Windows/blob/main/components/MarqueeText/src/MarqueeText.Properties.cs
        static void propertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void behaviorPropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void directionPropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void pauseOnHoverChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void spaceIntervalChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
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

        winrt::Windows::UI::Xaml::FrameworkElement rootGrid{ nullptr };
        winrt::Windows::UI::Xaml::Controls::Panel marqueeContainer{ nullptr };
        winrt::Windows::UI::Xaml::FrameworkElement segment1{ nullptr };
        winrt::Windows::UI::Xaml::FrameworkElement segment2{ nullptr };
        winrt::Windows::UI::Xaml::Media::TranslateTransform marqueeTransform{ nullptr };
        winrt::Windows::UI::Xaml::Media::Animation::Storyboard marqueeStoryboard{ nullptr };

        bool isActive{};
        void container_SizeChanged(winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);

        constexpr static std::wstring_view getVisualStateName(MarqueeDirection direction);
        constexpr static std::wstring_view getVisualStateName(MarqueeBehavior behavior);

        void startMarquee();
        void stopMarquee(bool initialState);

        bool updateAnimation(bool resume);

        winrt::event<UWPPackage::SignalDelegate> marqueeBegan;
        winrt::event<UWPPackage::SignalDelegate> marqueeStopped;
        winrt::event<UWPPackage::SignalDelegate> marqueeCompleted;

        winrt::event_token storyboardComplete_revoker;

        //bool isDirectionHorizontal();
        winrt::Windows::UI::Xaml::Media::Animation::Storyboard createStoryboard(
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

namespace winrt::UWPPackage::factory_implementation
{
    struct MarqueeText : MarqueeTextT<MarqueeText, implementation::MarqueeText>
    {
    };
}

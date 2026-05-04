#pragma once

#include "MarqueeText.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "include/TemplateControlHelper.hpp"

namespace winrt::PackageRoot::implementation
{
    struct MarqueeText : MarqueeTextT<MarqueeText>, TemplateControlHelper<MarqueeText>, EnsureDependencyProperty<MarqueeText>
    {
        static void EnsureDependencyProperties();
        MarqueeText() = default;

        void OnApplyTemplate();

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/MarqueeText_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/MarqueeText_Resource.xaml";
#endif
            
        double Speed();
        void Speed(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty SpeedProperty();

        winrt::WinUINamespace::UI::Xaml::Media::Animation::RepeatBehavior RepeatBehavior();
        void RepeatBehavior(winrt::WinUINamespace::UI::Xaml::Media::Animation::RepeatBehavior value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty RepeatBehaviorProperty();

        PackageRoot::MarqueeBehavior Behavior();
        void Behavior(PackageRoot::MarqueeBehavior value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty BehaviorProperty();

        PackageRoot::MarqueeDirection Direction();
        void Direction(PackageRoot::MarqueeDirection value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty DirectionProperty();

        winrt::hstring Text();
        void Text(winrt::hstring value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty TextProperty();

        bool PauseOnHover();
        void PauseOnHover(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty PauseOnHoverProperty();

        double IntervalSpace();
        void IntervalSpace(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IntervalSpaceProperty();

        void Pause();
        void Resume();
        void Reset();
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_speedProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_repeatBehaviorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_behaviorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_directionProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_textProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_pauseOnHoverProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_intervalSpaceProperty = nullptr;

        //https://github.com/CommunityToolkit/Labs-Windows/blob/main/components/MarqueeText/src/MarqueeText.Properties.cs
        static void propertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void behaviorPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void directionPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void pauseOnHoverChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void spaceIntervalChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
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

        winrt::WinUINamespace::UI::Xaml::FrameworkElement rootGrid{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Controls::Panel marqueeContainer{ nullptr };
        winrt::WinUINamespace::UI::Xaml::FrameworkElement segment1{ nullptr };
        winrt::WinUINamespace::UI::Xaml::FrameworkElement segment2{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Media::TranslateTransform marqueeTransform{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Media::Animation::Storyboard marqueeStoryboard{ nullptr };

        bool isActive{};
        void container_SizeChanged(winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e);

        constexpr static std::wstring_view getVisualStateName(MarqueeDirection direction);
        constexpr static std::wstring_view getVisualStateName(MarqueeBehavior behavior);

        void startMarquee();
        void stopMarquee(bool initialState);

        bool updateAnimation(bool resume);

        winrt::event<PackageRoot::SignalDelegate> marqueeBegan;
        winrt::event<PackageRoot::SignalDelegate> marqueeStopped;
        winrt::event<PackageRoot::SignalDelegate> marqueeCompleted;

        winrt::event_token storyboardComplete_revoker;

        //bool isDirectionHorizontal();
        winrt::WinUINamespace::UI::Xaml::Media::Animation::Storyboard createStoryboard(
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

namespace winrt::PackageRoot::factory_implementation
{
    struct MarqueeText : MarqueeTextT<MarqueeText, implementation::MarqueeText>
    {
    };
}

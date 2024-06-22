#include "pch.h"
#include "MarqueeText.h"
#if __has_include("MarqueeText.g.cpp")
#include "MarqueeText.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_speedProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Speed",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(32.), &MarqueeText::propertyChanged }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_repeatBehaviorProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"RepeatBehavior",
            winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehavior>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(
                    winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehaviorHelper::Forever()
                ),
                &MarqueeText::propertyChanged
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_behaviorProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Behavior",
            winrt::xaml_typename<WinUI3Package::MarqueeBehavior>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(WinUI3Package::MarqueeBehavior{}),
                &MarqueeText::behaviorPropertyChanged
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_directionProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Direction",
            winrt::xaml_typename<WinUI3Package::MarqueeDirection>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(WinUI3Package::MarqueeDirection::Left),
                &MarqueeText::directionPropertyChanged
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_textProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Text",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(L"")
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_pauseOnHoverProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"PauseOnHover",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                &MarqueeText::pauseOnHoverChanged
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::m_intervalSpaceProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"IntervalSpace",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<WinUI3Package::MarqueeText>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(64.),
                &MarqueeText::spaceIntervalChanged
            }
    );

    void MarqueeText::OnApplyTemplate()
    {
        base_type::OnApplyTemplate();
        auto test = GetTemplateChild(MarqueeTextPartName);
        marqueeContainer = GetTemplateChild(MarqueeTextPartName).as<decltype(marqueeContainer)>();
        segment1 = GetTemplateChild(Segment1PartName).as<decltype(segment1)>();
        segment2 = GetTemplateChild(Segment2PartName).as<decltype(segment2)>();
        marqueeTransform = GetTemplateChild(MarqueeTransformPartName).as<decltype(marqueeTransform)>();
        marqueeContainer.SizeChanged({ this, &MarqueeText::container_SizeChanged });
        rootGrid = GetTemplateChild(L"RootGrid").as<decltype(rootGrid)>();

        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, getVisualStateName(Direction()), false);
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, getVisualStateName(Behavior()), false);
    }

    double MarqueeText::Speed()
    {
        return winrt::unbox_value<double>(GetValue(m_speedProperty));
    }

    void MarqueeText::Speed(double value)
    {
        SetValue(m_speedProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::SpeedProperty()
    {
        return m_speedProperty;
    }

    winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehavior MarqueeText::RepeatBehavior()
    {
        return winrt::unbox_value<winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehavior>(
            GetValue(m_repeatBehaviorProperty)
        );
    }

    void MarqueeText::RepeatBehavior(winrt::Microsoft::UI::Xaml::Media::Animation::RepeatBehavior value)
    {
        SetValue(m_repeatBehaviorProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::RepeatBehaviorProperty()
    {
        return m_repeatBehaviorProperty;
    }

    WinUI3Package::MarqueeBehavior MarqueeText::Behavior()
    {
        return winrt::unbox_value<WinUI3Package::MarqueeBehavior>(
            GetValue(m_behaviorProperty)
        );
    }

    void MarqueeText::Behavior(WinUI3Package::MarqueeBehavior value)
    {
        SetValue(m_behaviorProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::BehaviorProperty()
    {
        return m_behaviorProperty;
    }

    WinUI3Package::MarqueeDirection MarqueeText::Direction()
    {
        return winrt::unbox_value<WinUI3Package::MarqueeDirection>(
            GetValue(m_directionProperty)
        );
    }

    void MarqueeText::Direction(WinUI3Package::MarqueeDirection value)
    {
        SetValue(m_directionProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::DirectionProperty()
    {
        return m_directionProperty;
    }

    winrt::hstring MarqueeText::Text()
    {
        return winrt::unbox_value<winrt::hstring>(GetValue(m_textProperty));
    }

    void MarqueeText::Text(winrt::hstring value)
    {
        SetValue(m_textProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::TextProperty()
    {
        return m_textProperty;
    }

    bool MarqueeText::PauseOnHover()
    {
        return winrt::unbox_value<bool>(GetValue(m_pauseOnHoverProperty));
    }

    void MarqueeText::PauseOnHover(bool value)
    {
        SetValue(m_pauseOnHoverProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::PauseOnHoverProperty()
    {
        return m_pauseOnHoverProperty;
    }

    double MarqueeText::IntervalSpace()
    {
        return winrt::unbox_value<double>(GetValue(m_intervalSpaceProperty));
    }

    void MarqueeText::IntervalSpace(double value)
    {
        SetValue(m_intervalSpaceProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty MarqueeText::IntervalSpaceProperty()
    {
        return m_intervalSpaceProperty;
    }

    void MarqueeText::Pause()
    {
        isPausing = true;
        if (marqueeStoryboard)
        {
            marqueeStoryboard.Pause();
        }
    }

    void MarqueeText::Resume()
    {
        isPausing = false;
        resumeStoryboardImpl();
    }

    void MarqueeText::Reset()
    {
        if (marqueeStoryboard)
        {
            marqueeStoryboard.Seek({});
            marqueeStoryboard.Begin();
        }
    }

    void MarqueeText::propertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto control = d.try_as<WinUI3Package::MarqueeText>())
        {
            winrt::get_self<MarqueeText>(control)->updateAnimation(true);
        }
    }

    void MarqueeText::behaviorPropertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto container = d.as<WinUI3Package::MarqueeText>();
        if (!container)
            return;

        auto control = winrt::get_self<MarqueeText>(container);
        bool const active = control->isActive;
        auto const newBehavior = winrt::unbox_value<MarqueeBehavior>(e.NewValue());
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(container, getVisualStateName(newBehavior), true);
        control->stopMarquee(false);
        //if (active)
        //    control->startMarquee();
        control->startMarquee();
    }

    void MarqueeText::directionPropertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto container = d.as<WinUI3Package::MarqueeText>();
        if (!container)
            return;

        auto control = winrt::get_self<MarqueeText>(container);
        bool const active = control->isActive;
        auto const oldDirection = winrt::unbox_value<MarqueeDirection>(e.OldValue());
        auto const newDirection = winrt::unbox_value<MarqueeDirection>(e.NewValue());
        auto const oldAxisX = isHorizontal(oldDirection);
        auto const newAxisX = isHorizontal(newDirection);

        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(container, getVisualStateName(newDirection), true);
        if (oldAxisX != newAxisX)
        {
            control->stopMarquee(false);
        }
        //if (active)
        //{
        //    control->startMarquee();
        //}
        control->startMarquee();
    }

    void MarqueeText::pauseOnHoverChanged(winrt::Microsoft::UI::Xaml::DependencyObject d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto container = d.as<WinUI3Package::MarqueeText>();
        if (!container)
            return;

        auto control = winrt::get_self<MarqueeText>(container);
        control->PointerEntered(control->pointerEntered_revoker);
        control->PointerExited(control->pointerExited_revoker);
        if (winrt::unbox_value<bool>(e.NewValue()))
        {
            control->pointerEntered_revoker = control->PointerEntered([weakSelf = control->get_weak()](auto...) {
                if (auto strongSelf = weakSelf.get())
                {
                    strongSelf->isHovering = true;
                    strongSelf->marqueeStoryboard.Pause();
                }
                });
            control->pointerExited_revoker = control->PointerExited([weakSelf = control->get_weak()](auto...) {
                if (auto strongSelf = weakSelf.get())
                {
                    strongSelf->isHovering = false;
                    strongSelf->resumeStoryboardImpl();
                }
                });
        }
    }

    void MarqueeText::spaceIntervalChanged(winrt::Microsoft::UI::Xaml::DependencyObject d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto container = d.as<WinUI3Package::MarqueeText>();
        if (!container)
            return;
        auto control = winrt::get_self<MarqueeText>(container);
        if (!control->rootGrid || control->Behavior() != MarqueeBehavior::Looping)
            return;

        for (auto visualStateGroup : winrt::Microsoft::UI::Xaml::VisualStateManager::GetVisualStateGroups(control->rootGrid))
        {
            for (auto visualState : visualStateGroup.States())
            {
                if (visualState.Name() == LoopingVisualStateName)
                {
                    auto const setter = (*visualState.Setters().First()).as<winrt::Microsoft::UI::Xaml::Setter>();
                    auto const oldPadding = setter.Value().as<winrt::Microsoft::UI::Xaml::Thickness>();
                    setter.Value(winrt::box_value(winrt::Microsoft::UI::Xaml::ThicknessHelper::FromLengths(
                        oldPadding.Left,
                        oldPadding.Top,
                        winrt::unbox_value<double>(e.NewValue()),
                        oldPadding.Bottom
                    )));
                    winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(container, L"EmptyBehaviorState", true);
                    winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(container, LoopingVisualStateName, true);
                    control->updateAnimation(true);
                    return;
                }
            }
        }

    }

    void MarqueeText::resumeStoryboardImpl()
    {
        if (!isHovering && !isPausing)
            marqueeStoryboard.Resume();
    }

    void MarqueeText::container_SizeChanged(winrt::Windows::Foundation::IInspectable sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
    {
        if (!marqueeContainer)
            return;

        //TODO: set clip in xaml?
        winrt::Microsoft::UI::Xaml::Media::RectangleGeometry rect;
        rect.Rect({ 0, 0, e.NewSize().Width, e.NewSize().Height });
        marqueeContainer.Clip(rect);
        startMarquee();
    }

    constexpr std::wstring_view MarqueeText::getVisualStateName(MarqueeDirection direction)
    {
        switch (direction)
        {
        case winrt::WinUI3Package::MarqueeDirection::Left: return LeftwardsVisualStateName;
        case winrt::WinUI3Package::MarqueeDirection::Right: return RightwardsVisualStateName;
        case winrt::WinUI3Package::MarqueeDirection::Up: return UpwardsVisualStateName;
        case winrt::WinUI3Package::MarqueeDirection::Down: return DownwardsVisualStateName;
        }
    }

    constexpr std::wstring_view MarqueeText::getVisualStateName(MarqueeBehavior behavior)
    {
        switch (behavior)
        {
        case winrt::WinUI3Package::MarqueeBehavior::Ticker: return TickerVisualStateName;
        case winrt::WinUI3Package::MarqueeBehavior::Looping: return LoopingVisualStateName;
        case winrt::WinUI3Package::MarqueeBehavior::Bouncing: return BouncingVisualStateName;
        }
    }

    void MarqueeText::startMarquee()
    {
        bool const initial = std::exchange(isActive, true);
        bool const playing = updateAnimation(initial);
        if (playing && !initial)
        {
            // Invoke MarqueeBegan if Marquee is now playing and was not before
            marqueeBegan();
        }
    }

    void MarqueeText::stopMarquee(bool initialState)
    {
        isActive = false;
        bool const playing = updateAnimation(false);
        if (!playing && initialState)
        {
            // Invoke MarqueeStopped if Marquee is not playing and was before
            marqueeStopped();
        }
    }

    bool MarqueeText::updateAnimation(bool resume)
    {
        if (!marqueeContainer ||
            !marqueeTransform ||
            !segment1 ||
            !segment2)
            return false;

        if (!isActive)
        {
            winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, MarqueeStoppedState, false);
            return false;
        }

        double containerSize{};
        double segmentSize{};
        double value{};
        std::wstring_view targetProperty;

        MarqueeDirection const direction = Direction();
        if (isHorizontal(direction))
        {
            containerSize = marqueeContainer.ActualWidth();
            segmentSize = segment1.ActualWidth();
            value = marqueeTransform.X();
            targetProperty = L"(TranslateTransform.X)";
        }
        else
        {
            //vertical direction
            containerSize = marqueeContainer.ActualHeight();
            segmentSize = segment1.ActualHeight();
            value = marqueeTransform.Y();
            targetProperty = L"(TranslateTransform.Y)";
        }

        MarqueeBehavior const behavior = Behavior();
        if (behavior == MarqueeBehavior::Looping && segmentSize < containerSize)
        {
            stopMarquee(resume);
            segment2.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
            return false;
        }

        /*
                    Initially:
                                                    container size
                                                |--------------------|
                                                some loooooooooooooooong marqueeing text
        -----------------------------------------------------------------------------------------------------
                    TickerMode:
                        start:
                                                    container size
                                                |--------------------|
                                                                     some loooooooooooooooong marqueeing text
                        end:
                                                    container size
                                                |--------------------|
        some loooooooooooooooong marqueeing text

        ------------------------------------------------------------------------------------------------------
                    BouncingMode:
                        start:
                                                    container size
                                                |--------------------|
                                                some loooooooooooooooong marqueeing text
                        end:
                                                    container size
                                                |--------------------|
                              some loooooooooooooooong marqueeing text
        ------------------------------------------------------------------------------------------------------

        */
        double start = behavior == MarqueeBehavior::Ticker ? containerSize : 0;
        double end = behavior == MarqueeBehavior::Bouncing ? -(segmentSize - containerSize) : -segmentSize;
        double const distance = std::abs(start - end);

        if (distance == 0) return false;
        if (direction == MarqueeDirection::Right || direction == MarqueeDirection::Down)
        {
            std::swap(start, end);
        }

        segment2.Visibility(behavior == MarqueeBehavior::Looping ? winrt::Microsoft::UI::Xaml::Visibility::Visible : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

        if (marqueeStoryboard)
        {
            marqueeStoryboard.Completed(storyboardComplete_revoker);
        }

        std::chrono::milliseconds const duration{ static_cast<int64_t>(distance / Speed() * 1000.0) };
        marqueeStoryboard = createStoryboard(
            start,
            end,
            duration,
            targetProperty
        );
        storyboardComplete_revoker = marqueeStoryboard.Completed({ this, &MarqueeText::storyboard_completed });
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, MarqueeActiveState, true);
        marqueeStoryboard.Begin();
        if (resume)
        {
            double const progress = std::abs(start - value) / distance;
            //marqueeStoryboard.Seek(winrt::Windows::Foundation::TimeSpan{ static_cast<int64_t>(duration.count() * progress * 10000) });
            auto const seekPosition = duration * progress;
            marqueeStoryboard.Seek(std::chrono::duration_cast<winrt::Windows::Foundation::TimeSpan>(seekPosition));
        }
        return true;
    }

    winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard MarqueeText::createStoryboard(
        double start,
        double end,
        winrt::Windows::Foundation::TimeSpan duration,
        std::wstring_view targetProperty)
    {
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard storyboard;
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimationUsingKeyFrames animation;
        winrt::Microsoft::UI::Xaml::Duration const d = winrt::Microsoft::UI::Xaml::DurationHelper::FromTimeSpan(duration);
        animation.Duration(d);
        animation.RepeatBehavior(RepeatBehavior());
        animation.AutoReverse(Behavior() == MarqueeBehavior::Bouncing);
        winrt::Microsoft::UI::Xaml::Media::Animation::LinearDoubleKeyFrame frame[2];
        frame[0].Value(start);
        frame[1].Value(end);
        frame[1].KeyTime({ duration });
        animation.KeyFrames().Append(frame[0]);
        animation.KeyFrames().Append(frame[1]);
        storyboard.Children().Append(animation);
        storyboard.Duration(d);
        storyboard.RepeatBehavior(RepeatBehavior());

        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard::SetTarget(animation, marqueeTransform);
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(animation, targetProperty);
        return storyboard;
    }

    void MarqueeText::storyboard_completed(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Windows::Foundation::IInspectable e)
    {
        stopMarquee(true);
        marqueeCompleted();
    }

    bool MarqueeText::isHorizontal(MarqueeDirection direction)
    {
        return direction == MarqueeDirection::Left || direction == MarqueeDirection::Right;
    }
}
